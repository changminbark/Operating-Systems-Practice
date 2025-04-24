import subprocess
import threading

def run_script():
    subprocess.run(["./sender", f"This is a message from thread {threading.current_thread().name}"])
    
threads = []
    
for i in range(20):
    t = threading.Thread(target=run_script, name=f"Thread-{i}")
    threads.append(t)
    t.start()
    
for t in threads:
    t.join()