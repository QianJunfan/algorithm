# It scans .cpp files in the current directory to extract problem info and dates
# from comments. 
# It then generates a character-based heatmap and a chronological activity log.

import os, re
from datetime import datetime, timedelta
from collections import defaultdict

SEP = "-"

def get_db():
    db = defaultdict(list)
    # Regex for title and date extraction
    h_re = re.compile(r"/\*\s*(.*?)\s*\n\s*\*\s*([A-Z][a-z]{2}\s\d{1,2},\s\d{4})")
    n_re = re.compile(r"/\*.*?\*/", re.DOTALL)
    
    for f in [f for f in os.listdir('.') if f.endswith('.cpp')]:
        try:
            with open(f, 'r', encoding='utf-8') as s:
                raw = s.read(2000)
                h = h_re.search(raw)
                if not h: continue
                
                # Metadata parsing
                ttl_f, d_str = h.group(1).strip(), h.group(2).strip()
                dt = datetime.strptime(d_str, "%b %d, %Y").date()
                pts = ttl_f.split('-', 1)
                idx, name = pts[0].strip(), (pts[1].strip() if len(pts) > 1 else "")
                
                # Content cleaning
                blk = n_re.search(raw)
                n = []
                if blk:
                    for l in blk.group(0).split('\n'):
                        c = l.replace('/*', '').replace('*/', '').replace('*', '').replace('/', '').strip()
                        if c and c not in (ttl_f, d_str): n.append(c)
                
                db[dt].append({'idx': idx, 'name': name, 'n': n, 'f': f"[{f}]"})
        except: continue
    return db

def glyph(n, ftr):
    # Map frequency to density levels
    return "*" if ftr else "░▒▓█"[(n > 0) + (n > 3) + (n > 8)]

def run():
    print("Activity log and heatmap provided by sc.py.\n")
    db, td = get_db(), datetime.now().date()
    cnts = {k: len(v) for k, v in db.items()}
    
    # Calculate grid range (past 30 weeks)
    start = td - timedelta(days=(td.weekday() + 1) % 7, weeks=29)
    grid = {d: [] for d in ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"]}

    for i in range(210):
        curr = start + timedelta(days=i)
        grid[curr.strftime("%a")].append(glyph(cnts.get(curr, 0), curr > td))

    # Render heatmap rows
    for d in ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"]:
        print(f"        {d} {' '.join(grid[d])}")
    
    ltst = max(db.keys() or [td])
    print(f"\n        Latest: {ltst}, ░:[0], ▒:(0,3], ▓:(3,8], █:(8,∞), *:Future\n" + " " * 8 + "-" * 63 + "\n\n")

    # Render chronological log
    for dt in sorted(db.keys(), reverse=True):
        print(f"{dt.strftime('%b %d, %Y')}:")
        m_w = max(len(i['idx']) for i in db[dt]) + 1
        for i in db[dt]:
            l_p = f"        {i['idx'] :<{m_w}}{SEP} {i['name']}"
            print(f"{l_p:<{80-len(i['f'])}}{i['f']}")
            if i['n']:
                print(f"        ╰─> {i['n'][0]}")
                for ln in i['n'][1:]: print(f"            {ln}")
                print()
        print()

if __name__ == "__main__":
    run()
