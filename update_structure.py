import os
import shutil

base_dir = r"d:\ALLYEARS"

folders_to_delete = [
    r"Year 1\Semester 1\Programare in C",
    r"Year 1\Semester 1\Psihologie educationala (facultativ)",
    r"Year 1\Semester 2\Metode avansate de rezolvare a problemelor de matematica si informatica",
    r"Year 2\Semester 1\Teoria si metodologia instruirii. Teoria si metodologia evaluarii",
    r"Year 2\Semester 2\Didactica Informaticii",
    r"Year 3\Semester 1\Aplicatii ale geometriei in informatica",
    r"Year 3\Semester 1\Arhitectura aplicatiilor cloud",
    r"Year 3\Semester 1\Criptografie cu cheie publica (in engleza)",
    r"Year 3\Semester 1\Demonstrare automata cu Lean",
    r"Year 3\Semester 1\Instruire asistata de calculator",
    r"Year 3\Semester 1\Instrumente CASE",
    r"Year 3\Semester 1\Interactiunea om-calculator",
    r"Year 3\Semester 1\Proiect de cercetare",
    r"Year 3\Semester 1\Proiectarea produselor inovative",
    r"Year 3\Semester 1\Realitate virtuala",
    r"Year 3\Semester 1\Roboti inteligenti"
]

# Delete folders
for f in folders_to_delete:
    path = os.path.join(base_dir, f)
    if os.path.exists(path):
        shutil.rmtree(path)
        print(f"Deleted: {path}")
    else:
        print(f"Not found: {path}")

subfolders_to_create = [
    "photos",
    "seminar",
    "course",
    "laboratory",
    "exam materials",
    "other materials"
]

# Walk through to find subject folders
for year in ["Year 1", "Year 2", "Year 3"]:
    for sem in ["Semester 1", "Semester 2"]:
        sem_path = os.path.join(base_dir, year, sem)
        if not os.path.exists(sem_path):
            continue
        for subject in os.listdir(sem_path):
            subject_path = os.path.join(sem_path, subject)
            if os.path.isdir(subject_path):
                # Delete old .gitkeep if exists
                old_gitkeep = os.path.join(subject_path, ".gitkeep")
                if os.path.exists(old_gitkeep):
                    os.remove(old_gitkeep)
                
                # Create subfolders
                for sub in subfolders_to_create:
                    sub_path = os.path.join(subject_path, sub)
                    os.makedirs(sub_path, exist_ok=True)
                    # Create .gitkeep in subfolder
                    with open(os.path.join(sub_path, ".gitkeep"), 'w') as f:
                        pass
                print(f"Structured: {subject_path}")
