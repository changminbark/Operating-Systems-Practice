import subprocess
import csv
from scipy import stats

policies = 3
R_samples = 50
n_iterations = 100
sample_mean = 0

data = []

for algo in range(policies):
    with open(f"exp-results_{algo}.csv", mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["Run number", "Seed value", "Average frag"])
    for i in range(R_samples):
        result = subprocess.run(["../bin/frag-eval", f"{algo}", f"{i}", f"{n_iterations}"], capture_output=True, text=True)
        lines = result.stdout.splitlines()
        value = "N/A"  # fallback if line isn't found
        for line in lines:
            if line.startswith("Average fragmentation:"):
                value = line.split(":")[1].strip()
                sample_mean += float(value)
                data.append(float(value))
                break
        
        with open(f"exp-results_{algo}.csv", mode='a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow([i, i, value]) 
    
    # Calculate sample mean, stdev, and t-score
    sample_mean /= R_samples
    stdev = stats.tstd(data)
    sem = stdev / (R_samples ** 0.5)
    t_score = stats.t.interval(
        confidence=0.95, 
        df=R_samples - 1,
        loc=sample_mean,
        scale=sem
    )
    with open(f"exp-results_{algo}.csv", mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["sample mean", "standard deviation", "standard error of the mean", "confidence interval 95%"]) 
        writer.writerow([sample_mean, stdev, sem, t_score]) 
    
            