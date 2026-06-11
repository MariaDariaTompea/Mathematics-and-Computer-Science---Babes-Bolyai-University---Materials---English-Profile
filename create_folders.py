import urllib.request
import re
import os

urls = {
    'Year 1/Semester 1': 'https://www.cs.ubbcluj.ro/files/orar/2025-1/tabelar/IE1.html',
    'Year 1/Semester 2': 'https://www.cs.ubbcluj.ro/files/orar/2025-2/tabelar/IE1.html',
    'Year 2/Semester 1': 'https://www.cs.ubbcluj.ro/files/orar/2025-1/tabelar/IE2.html',
    'Year 2/Semester 2': 'https://www.cs.ubbcluj.ro/files/orar/2025-2/tabelar/IE2.html',
    'Year 3/Semester 1': 'https://www.cs.ubbcluj.ro/files/orar/2025-1/tabelar/IE3.html',
    'Year 3/Semester 2': 'https://www.cs.ubbcluj.ro/files/orar/2025-2/tabelar/IE3.html',
}

def clean_filename(name):
    return re.sub(r'[\\\\/*?:\'\"<>|]', '', name).strip()

for path, url in urls.items():
    try:
        req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
        html = urllib.request.urlopen(req).read().decode('utf-8')
        # find all <a href="../disc/...html" >Subject</a>
        matches = re.findall(r'<a href=\"\.\./disc/[^\"]+\"\s*>(.*?)</a>', html)
        subjects = set(matches)
        
        for subject in subjects:
            folder_path = os.path.join(path, clean_filename(subject))
            os.makedirs(folder_path, exist_ok=True)
            print(f'Created: {folder_path}')
    except Exception as e:
        print(f'Error on {url}: {e}')
