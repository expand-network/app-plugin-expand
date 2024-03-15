ethereum_address = "0xa5588f7cdf560811710a2d82d3c9c99769db1dcb"

# Remove the '0x' prefix and convert to lowercase
ethereum_address = ethereum_address[2:].lower()

# Break down the address into pairs of characters
pairs = [ethereum_address[i:i+2] for i in range(0, len(ethereum_address), 2)]

# Convert each pair of hexadecimal characters to its decimal equivalent
decimal_format = [int(pair, 16) for pair in pairs]

# Format the decimal values as requested
formatted_address = "{ " + ", ".join([f"0x{val:02x}" for val in decimal_format]) + " };"

print(formatted_address)
