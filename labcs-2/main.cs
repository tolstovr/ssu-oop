using System;

class Program {
  static void Main(string[] args) {
    Console.Write("Enter the size of the array n (a positive integer): ");
    
    if (!int.TryParse(Console.ReadLine(), out int n) || n <= 0) {
      Console.WriteLine("Error: The size of the array must be a positive integer.");
      return;
    }
    
    int[,] array = new int[n, n];
    Console.WriteLine("Enter the elements of the array (row by row):");

    for (int i = 0; i < n; i++) {
      Console.Write($"Row {i + 1}: ");
      string[] input = Console.ReadLine().Split(' ');

      if (input.Length != n) {
        Console.WriteLine($"Error: Each row must contain {n} elements.");
        return;
      }

      for (int j = 0; j < n; j++) {
        if (!int.TryParse(input[j], out array[i, j])) {
          Console.WriteLine($"Error: Element '{input[j]}' is not an integer.");
          return;
        }
      }
    }

    int[] X = new int[n];
    Console.WriteLine("Enter the elements of vector X (space-separated):");

    string[] xInput = Console.ReadLine().Split(' ');

    if (xInput.Length != n) {
      Console.WriteLine($"Error: Vector X must contain {n} elements.");
      return;
    }

    for (int i = 0; i < n; i++) {
      if (!int.TryParse(xInput[i], out X[i])) {
        Console.WriteLine($"Error: Element '{xInput[i]}' is not an integer.");
        return;
      }
    }

    for (int j = 0; j < n; j++) {
      if (j % 2 == 0) {
        for (int i = 0; i < n; i++) {
          array[i, j] = X[i];
        }
      }
    }

    Console.WriteLine("\nArray after replacing even columns:");
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        Console.Write(array[i, j] + "\t");
      }

      Console.WriteLine();
    }
  }
}