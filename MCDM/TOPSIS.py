import math
from decimal import Decimal
# Moving from Excel Spreadsheet to python 
# More automatic

DEBUG:bool = False
VERBOSE:bool = False

MANUFACTURERS = [
    "autosen",
    "Vutlan",
	"Strainsense",
	"KEMET",
	"Witmotion1",
	"Witmotion2",
	"IFM	",
    "RS-PRO",
    "CTC",
	"ADAFRUIT"
    ]


META_LINES = ["Candidate", "Manufacturer"]

if __name__ == "__main__":
    meta_content = []
    crit_content = []
    crit_weights = []
    cost_benefit = []
    with open("MCDM\\Specification_Matrix.csv", "r") as f:
        lines = f.readlines()
        #meta_content.append(lines.pop(0))
        for line in lines:
            line_values = line.replace("\n", "").split(",")
            cost_benefit_val = line_values[0]
            line_meta = line_values[1] # Lines Purpose/title
            weight = line_values[2]
            candidate_values = line_values[3:]
            if line_meta in META_LINES:
                # Candidate names, Manufaturer (Non scoring Lines)
                meta_content.append((line_meta, candidate_values))
            else:
                # Numerical Values for criteria (Criteria Scoring Lines)
                crit_weights.append(Decimal(weight))
                cost_benefit.append(cost_benefit_val)
                crit_content.append((line_meta, [Decimal(v) for v in candidate_values]))

            

    # Normalise Weights (weights sum must == 1)
    weights_sum:Decimal = sum(crit_weights)
    NORMALISED_WEIGHTS = 0 if weights_sum == 0 else [weight/weights_sum for weight in crit_weights]
    if DEBUG:
        print(sum(crit_weights))
        print(sum(NORMALISED_WEIGHTS))


    # Compute Normalised Matrix
    normalised_matrix = []
    for criteria in crit_content:
        denominator = Decimal(math.sqrt(sum([i**2 for i in criteria[1]])))
        normalised_matrix.append((
            criteria[0], [criteria[1][i]/denominator for i in range(len(criteria[1]))]
            )
        )



    # Compute Weighted Normalised Matrix
    weighted_normalised_matrix = []
    for i, criteria in enumerate(normalised_matrix):
        weighted_normalised_matrix.append((
                criteria[0], [c*NORMALISED_WEIGHTS[i] for c in criteria[1]]
            )
        )


    # Ideal Best & Worst
    best_scores = [
        max(weighted_normalised_matrix[i][1]) if cost_benefit[i] == "Benefit" else min(weighted_normalised_matrix[i][1]) 
        for i in range(len(weighted_normalised_matrix))]
    worst_scores = [
        min(weighted_normalised_matrix[i][1]) if cost_benefit[i] == "Benefit" else max(weighted_normalised_matrix[i][1]) 
        for i in range(len(weighted_normalised_matrix))
    ]

    # SI+ & SI-
    candidate_scores = [[i, Decimal()] for i in meta_content[0][1]]
    candidates_positive_distance = [[i, Decimal()] for i in meta_content[0][1]]
    candidates_negative_distance = [[i, Decimal()] for i in meta_content[0][1]]

    for i, criteria in enumerate(weighted_normalised_matrix):
        #candidate_scores = criteria[1]
        for j in range(len(candidate_scores)):          
            candidates_positive_distance[j][1] += Decimal((criteria[1][j] - best_scores[j])**2)
            candidates_negative_distance[j][1] += Decimal((criteria[1][j] - worst_scores[j])**2)
            
    for i in range(len(candidates_positive_distance)):
        candidates_positive_distance[i][1] = math.sqrt(candidates_positive_distance[i][1])
        candidates_negative_distance[i][1] = math.sqrt(candidates_negative_distance[i][1])

    # Rankings
    PIS = [(meta_content[0][1][i], candidates_negative_distance[i][1]/(candidates_positive_distance[i][1]+candidates_negative_distance[i][1])) for i in range(len(meta_content[0][1]))]
    PIS.sort(key=lambda pair: pair[1], reverse=True)
    for i, ranking in enumerate(PIS):
        print(f"{i+1}: {ranking[0]} {'('+str(ranking[1])+')' if VERBOSE else ''}")