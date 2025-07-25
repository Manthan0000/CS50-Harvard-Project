import csv
import sys

def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        return

    # Read database file into a variable
    database = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            for key in row.keys():
                if key != "name":
                    row[key] = int(row[key])
            database.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        sequence = file.read()

    # Find longest match of each STR in DNA sequence
    str_counts = {}
    for str_seq in database[0].keys():
        if str_seq != "name":
            str_counts[str_seq] = longest_match(sequence, str_seq)

    # Check database for matching profiles
    for person in database:
        if all(person[str_seq] == str_counts[str_seq] for str_seq in str_counts):
            print(person["name"])
            return

    print("No match")

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)
    for i in range(sequence_length):
        count = 0
        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break
        longest_run = max(longest_run, count)
    return longest_run

if __name__ == "__main__":
    main()
