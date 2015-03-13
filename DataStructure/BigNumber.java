
/**
  * Big number multiplication.
  */
String multiply(String num1, String num2) {
  char[] numChars1 = new StringBuffer(num1).reverse().toString().toCharArray();
  char[] numChars2 = new StringBuffer(num2).reverse().toString().toCharArray();


  int[] digits = new int[num1.length() + num2.length() + 1];// +1 for outflow index guard

  for (int i = 0; i < numChars1.length; i++) {
    for (int j = 0; j < numChars2.length; j++) {
      digits[i+j] += (numChars1[i] - '0') * (numChars2[j] - '0');
    }
  }
  for (int i = 0; i < numChars1.length + numChars2.length; i++) {
    digits[i + 1] += digits[i] / 10;
    digits[i] %= 10;
  }
  StringBuilder sb = new StringBuilder();
  for (int i = numChars1.length + numChars2.length - 1; i >= 0; i--) {
    if (sb.length() == 0 && digits[i] == 0 && i > 0) continue; // remove pending zero
    sb.append(digits[i]);
  }
  return sb.toString();
}
