import pandas as pd

def c_code(df, sym_col, stat_col):
    df['c_code'] = df.apply(lambda row: f"    {row[sym_col]} = {int('0x' + str(row[stat_col]), 16)},", axis=1)
    max_length = df['c_code'].str.len().max()
    df['c_comment'] = df.apply(lambda row: f"{(2 + (max_length - len(row['c_code']))) * ' '}// 0x{row[stat_col]}\n", axis=1)

def main():
    status_df = pd.read_csv("status.csv")
    response_df = pd.read_csv("response.csv")

    # C code
    c_code(status_df, "SYMBOL", "Status")
    c_code(response_df, "SYMBOL", "Status")
    
    with open("c_status", 'w') as c_out:
        c_out.write("enum status\n{\n")
        for _, row in status_df.iterrows():
            c_out.write(f"{row['c_code']}{row['c_comment']}")
        c_out.write("};")

        c_out.write("\n\n")
        c_out.write("enum response\n{\n")
        for _, row in response_df.iterrows():
            c_out.write(f"{row['c_code']}{row['c_comment']}")
        c_out.write("};")



if __name__ == '__main__':
    main()
