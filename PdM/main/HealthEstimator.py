import os
from tensorflow import keras
from keras import Sequential
from keras.layers import LSTM, RepeatVector, TimeDistributed, Dense

import pandas as pd
import numpy as np

from sklearn.cluster import KMeans

from DatasetCollection import feature_extraction, feature_standardise


DATAPOINTS_PER_FILE = 20480
SAMPLE_RATE = 20000 # 20 kHz


# Features
features_df = feature_extraction()
features_scaled = feature_standardise(features_df)

# Clustering
kmeans = KMeans(n_clusters=2, random_state=42).fit(features_scaled.values) # Do not include RUL nor time-indexing (just the feature columns)
features_scaled["cluster_labels"] = kmeans.labels_

# Aggregate by label (0, 1)
cluster_means = features_scaled.groupby("cluster_labels").mean()
print(cluster_means[["rms", "kurtosis", "spectral_entropy"]])

print(features_scaled)


if False:
    class HealthIndexEstimator:
        def __init__(self, layers:list, data):
            #super.__init__(layers)
            self.sequential_layers:list = layers


            self.MODELS_LOCATION = "./models/"
            self.dataset:pd.DataFrame = pd.DataFrame(data)



        def construct(self):
            pass

        def feature_extraction(self, csv_delemiter="\t"):
            pass





    SEQUENCE_LENGTH = 20
    FEATURES_COUNT = 11

    autoencoder = Autoencoder([
        # Input Layer - Using ReLU as paper, if large reconstruction error or dead neurons detected tne use tanh
        LSTM(64, activation="ReLU", input_shape=(SEQUENCE_LENGTH, FEATURES_COUNT), return_sequences=False),
        RepeatVector(SEQUENCE_LENGTH), 
        # Output Layer
        LSTM(64, activation="ReLU", return_sequences=True),
        TimeDistributed(Dense(FEATURES_COUNT))
    ]
    , data=[]
    )

    # Import Dataset
    DATASET_LOC = "./Datasets/"
    NASA_BEARING_DATASET_LOC = DATASET_LOC + "NASABearing/"
    DEBUG = True

    # For all sets_directories (not files) in dataset dir - Path.join is concatenates full path str lit to directory
    sets_directories = [os.path.join(NASA_BEARING_DATASET_LOC, d)+f"/{d}/" for d in  os.listdir(NASA_BEARING_DATASET_LOC) if os.path.isdir(os.path.join(NASA_BEARING_DATASET_LOC, d))]

    ## Select Dataset ##
    DATASET_DIR_INUSE = sets_directories[0]

    if DEBUG:
        print("Available sets in Dataset are:")
        for i, dir in enumerate(sets_directories):
            print(f"[{i}] {dir}")
        # Using set/run 2
        print(f"Using set: {DATASET_DIR_INUSE}")


    print(f"Count of bursts/files: {len(os.listdir(DATASET_DIR_INUSE))}")