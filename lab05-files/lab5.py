#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import pandas as pd

def main():

    drivers_df = pd.read_csv("drivers.csv")
    results_df = pd.read_csv("results.csv")
    merged_df = pd.merge(drivers_df, results_df, on = "driverId")
    
    column_sort = "nationality"
    sorted_df = merged_df.sort_values(by = column_sort)
    winners_df = sorted_df[sorted_df["position"] == "1"]
    
    nationality_count = {}

    for index, row in winners_df.iterrows():
        nationality = row["nationality"]

        if nationality not in nationality_count:
            nationality_count[nationality] = 1
        else:
            nationality_count[nationality] += 1
    
    sorted_dict = dict(sorted(nationality_count.items(), key=lambda item: item[1], reverse = True))
    
    print("\nTop 10 winners\n")
    count = 0
    for key, value in sorted_dict.items():
        print(f"{key}: {value}")
        count += 1
        if count == 10:
            print()
            break


if __name__ == "__main__":
    main()
