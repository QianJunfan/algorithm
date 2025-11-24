#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <ctype.h>

#define MAX_PATH_LEN                    256
#define MAX_PROBLEMS_PER_FILE           256
#define MAX_PROBLEM_NAME_LEN            128
#define MAX_DESCRIPTION_LEN             2048
#define LOG_FILENAME                    "log"
#define FILENAME_DATE_FORMAT_C          "%b_%d_%Y"
#define MAX_FILE_ENTRIES                1024

struct problem {
	char num[8];
	char name[MAX_PROBLEM_NAME_LEN];
};

struct file_entry {
	char filename[MAX_PATH_LEN];
	struct tm date;
	struct problem problems[MAX_PROBLEMS_PER_FILE];
	int num_problems;
	char description[MAX_DESCRIPTION_LEN];
};

static int parse_date(const char *filename, struct tm *date)
{
	char date_str[MAX_PATH_LEN];
	char *end_ext;

	strncpy(date_str, filename, MAX_PATH_LEN - 1);
	date_str[MAX_PATH_LEN - 1] = '\0';

	end_ext = strrchr(date_str, '.');
	if (end_ext == NULL || strcmp(end_ext, ".c") != 0)
		return -1;

	*end_ext = '\0';

	if (strptime(date_str, FILENAME_DATE_FORMAT_C, date) == NULL)
		return -1;

	return 0;
}

static int compare_problems(const void *a, const void *b)
{
	const struct problem *prob_a = a;
	const struct problem *prob_b = b;

	return strcmp(prob_a->num, prob_b->num);
}

static int parse_c_file(const char *filepath, struct file_entry *entry)
{
	FILE *fp;
	char line[MAX_PATH_LEN];
	const char *prefix = "/* ";
	char desc_buf[MAX_DESCRIPTION_LEN] = "";
	int in_block_comment = 0;
	long start_of_problems_pos = 0;
	int i = 0;

	fp = fopen(filepath, "r");
	if (!fp)
		return -1;

	entry->description[0] = '\0';
	entry->num_problems = 0;

	while (fgets(line, sizeof(line), fp)) {
		char *trimmed_line = line;

		if (!in_block_comment) {
			while (isspace((unsigned char)*trimmed_line))
				trimmed_line++;

			if (trimmed_line[0] == '\0')
				continue;
			if (trimmed_line[0] == '#')
				continue;
		}

		if (strstr(line, "/*") && !in_block_comment) {
			in_block_comment = 1;
			continue;
		}

		if (in_block_comment) {
			char *end_comment = strstr(line, "*/");

			if (end_comment) {
				*end_comment = '\0';
				in_block_comment = 0;
				start_of_problems_pos = ftell(fp);
				break;
			}

			while (*trimmed_line && (isspace((unsigned char)*trimmed_line) ||
					 *trimmed_line == '*'))
				trimmed_line++;

			if (*trimmed_line == '\0') {
				if (strlen(desc_buf) + 1 < MAX_DESCRIPTION_LEN)
					strcat(desc_buf, "\n");
				continue;
			}

			if (strlen(desc_buf) + strlen(trimmed_line) + 1 <
					MAX_DESCRIPTION_LEN) {
				strcat(desc_buf, trimmed_line);
			}
		}

		if (!in_block_comment && strlen(desc_buf) > 0) {
			start_of_problems_pos = ftell(fp);
			break;
		}
	}

	if (strlen(desc_buf) > 0) {
		strncpy(entry->description, desc_buf, MAX_DESCRIPTION_LEN - 1);
		entry->description[MAX_DESCRIPTION_LEN - 1] = '\0';
	}

	if (start_of_problems_pos != 0)
		fseek(fp, start_of_problems_pos, SEEK_SET);
	else
		fseek(fp, 0, SEEK_SET);

	while (fgets(line, sizeof(line), fp)) {
		char *start = strstr(line, prefix);
		char *p_num;
		char *p_name_start;
		char *p_name_end;
		struct problem *prob;

		if (!start)
			continue;

		p_num = start + strlen(prefix);

		if (sscanf(p_num, "%7s - %*[^\n]", entry->problems[i].num) != 1)
			continue;

		p_name_start = strstr(p_num, " - ");
		if (!p_name_start)
			continue;

		p_name_start += 3;

		p_name_end = strstr(p_name_start, "\n");
		if (p_name_end)
			*p_name_end = '\0';

		p_name_end = strstr(p_name_start, "*/");
		if (p_name_end)
			*p_name_end = '\0';

		prob = &entry->problems[i];
		strncpy(prob->name, p_name_start, MAX_PROBLEM_NAME_LEN - 1);
		prob->name[MAX_PROBLEM_NAME_LEN - 1] = '\0';

		if (strstr(prob->name, "from https://"))
			continue;

		if (prob->name[0] == '\0')
			continue;

		entry->num_problems++;
		i++;
		if (i >= MAX_PROBLEMS_PER_FILE)
			break;
	}

	fclose(fp);

	if (entry->num_problems > 0) {
		int write_idx = 1;

		qsort(entry->problems, entry->num_problems,
			  sizeof(struct problem), compare_problems);

		if (entry->num_problems > 1) {
			for (int read_idx = 1; read_idx < entry->num_problems; read_idx++) {
				if (strcmp(entry->problems[read_idx].num,
						   entry->problems[write_idx - 1].num) != 0 ||
					strcmp(entry->problems[read_idx].name,
						   entry->problems[write_idx - 1].name) != 0) {
					if (write_idx != read_idx)
						entry->problems[write_idx] =
							entry->problems[read_idx];
					write_idx++;
				}
			}
			entry->num_problems = write_idx;
		}
	}

	return 0;
}

static int compare_entries(const void *a, const void *b)
{
	const struct file_entry *entry_a = a;
	const struct file_entry *entry_b = b;
	time_t time_a;
	time_t time_b;

	time_a = mktime((struct tm *)&entry_a->date);
	time_b = mktime((struct tm *)&entry_b->date);

	if (time_a < time_b)
		return 1;
	if (time_a > time_b)
		return -1;
	return 0;
}

static int write_log(struct file_entry *entries, int num_entries)
{
	FILE *fp;
	int i;
	int j;
	char date_buf[MAX_PATH_LEN];
	char *desc_line;

	fp = fopen(LOG_FILENAME, "w");
	if (!fp)
		return -1;

	fprintf(fp, "Automatically generated by alfred, this log details all my "
		"problem-solving entries and their dates.\n\n");

	for (i = 0; i < num_entries; i++) {
		if (strftime(date_buf, sizeof(date_buf), "%a, %b %d, %Y",
			     &entries[i].date) == 0) {
			fclose(fp);
			return -1;
		}

		fprintf(fp, "\n%s:\n", date_buf);

		if (entries[i].description[0] != '\0') {
			desc_line = entries[i].description;
			while (*desc_line) {
				char *newline = strchr(desc_line, '\n');

				if (newline)
					*newline = '\0';

				fprintf(fp, "        %s\n", desc_line);

				if (newline) {
					*newline = '\n';
					desc_line = newline + 1;
				} else {
					break;
				}
			}
		}

		for (j = 0; j < entries[i].num_problems; j++) {
			struct problem *prob = &entries[i].problems[j];

			fprintf(fp, "        %s - %s\n", prob->num, prob->name);
		}
	}
	fprintf(fp, "\n");

	fclose(fp);
	return 0;
}

int main(void)
{
	DIR *dir;
	struct dirent *dp;
	struct file_entry *entries;
	int count = 0;
	int i;

	entries = calloc(MAX_FILE_ENTRIES, sizeof(*entries));
	if (!entries)
		return 1;

	dir = opendir(".");
	if (!dir) {
		free(entries);
		return 1;
	}

	while ((dp = readdir(dir))) {
		if (dp->d_type == DT_REG && strstr(dp->d_name, ".c")) {
			if (parse_date(dp->d_name, &entries[count].date) == 0) {
				strncpy(entries[count].filename, dp->d_name,
					MAX_PATH_LEN - 1);
				entries[count].filename[MAX_PATH_LEN - 1] = '\0';
				count++;
			}
		}
	}
	closedir(dir);

	for (i = 0; i < count; i++) {
		if (parse_c_file(entries[i].filename, &entries[i]) != 0) {
			free(entries);
			return 1;
		}
	}

	qsort(entries, count, sizeof(*entries), compare_entries);

	if (write_log(entries, count) != 0) {
		free(entries);
		return 1;
	}

	free(entries);
	return 0;
}
