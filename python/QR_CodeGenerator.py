# Uses the third-party library `qrcode`
# You must install it using: pip install qrcode[pil]

import qrcode

# Get user input
data = input('Enter the text or URL: ').strip()
filename = input('Enter the filename (e.g., mycode.png): ').strip()

# Create QR code object
qr = qrcode.QRCode(
    version=1,         # controls size of the QR Code
    box_size=10,       # size of each box in pixels
    border=4           # thickness of the border
)

# Add data to the QR code
qr.add_data(data)
qr.make(fit=True)

# Create and save the image
image = qr.make_image(fill_color='black', back_color='white')
image.save(filename)

print(f'✅ QR code saved as {filename}')
