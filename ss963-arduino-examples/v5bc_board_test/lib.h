
/*
 * Converts 'ports' bit array to bytes array.
 * After, bytes array will transmit to SPI port.
 */
void convert_bit_array_to_byte_array(byte *ports, byte *byte_array) {
  int i, j;
  for (i = 0; i < PORT_COUNT/8; i++)
  {
    byte_array[i] = 0;
    for (j = 0; j < 8; j++)
      byte_array[i] += ports[i * 8 + j] << j;
  }
}

/*
 * Set all ports of card to LOW or HIGH.
 * Not critial.
 */
void fill_ports(byte *ports, byte on_off)
{
  int i;
  for (i = 0; i < PORT_COUNT; i++)
    ports[i] = on_off;
}

/*
 * Do latch.
 * The latch function writes buffer registers to outs.
 */
void latch() {
  digitalWrite(LATCH_PIN, HIGH);
  delay(LATCH_DELAY_MS);
  digitalWrite(LATCH_PIN, LOW);
}

/*
 * Store ports array data to card's buffer registers.
 */
void write_ports(byte *ports)
{
  convert_bit_array_to_byte_array(ports, byte_array);
  int j;
  for (j = (PORT_COUNT/8)-1; j >= 0; j--) {
    SPI.transfer(byte_array[j]);
  }

  latch();
}
