using System;
using System.Collections.Generic;

public class Matrix
{
    private short[,] elements;
    private int rows;
    private int cols;

    // Constructor that allows specifying the dimensions of the matrix
    public Matrix(int rows, int cols)
    {
        if (rows <= 0 || cols <= 0)
        {
            throw new ArgumentException("Matrix dimensions must be positive.");
        }

        this.rows = rows;
        this.cols = cols;
        elements = new short[rows, cols];
    }

    // Copy constructor
    public Matrix(Matrix other)
    {
        this.rows = other.rows;
        this.cols = other.cols;
        elements = new short[rows, cols];

        // Copying elements from another matrix
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                elements[i, j] = other.elements[i, j];
            }
        }
    }

    // Properties to get the number of rows and columns
    public int Rows => rows;
    public int Cols => cols;

    // Method to fill the matrix with values from the user
    public void FillMatrix()
    {
        Console.WriteLine($"Enter elements for a matrix of size {rows}x{cols}:");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                while (true)
                {
                    Console.Write($"Element [{i}, {j}]: ");
                    string input = Console.ReadLine();
                    if (short.TryParse(input, out short value))
                    {
                        elements[i, j] = value;
                        break;
                    }
                    else
                    {
                        Console.WriteLine("Error: please enter a valid short integer.");
                    }
                }
            }
        }
    }

    // Method to fill the matrix with zeros
    public void Reset()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                elements[i, j] = 0;
            }
        }
        Console.WriteLine("Matrix has been reset and filled with zeros.");
    }

    // Indexer for accessing matrix elements
    public short this[int row, int col]
    {
        get
        {
            if (row < 0 || row >= rows || col < 0 || col >= cols)
            {
                throw new IndexOutOfRangeException("Index is out of bounds of the matrix.");
            }
            return elements[row, col];
        }
        set
        {
            if (row < 0 || row >= rows || col < 0 || col >= cols)
            {
                throw new IndexOutOfRangeException("Index is out of bounds of the matrix.");
            }
            elements[row, col] = value;
        }
    }

    // Method to display the matrix
    public void Display()
    {
        Console.WriteLine("Matrix:");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                Console.Write(elements[i, j] + "\t");
            }
            Console.WriteLine();
        }
    }

    // Method to calculate the average of the matrix elements
    public double Average()
    {
        double sum = 0;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                sum += elements[i, j];
            }
        }

        return sum / (rows * cols);
    }

    // Method to resize the matrix
    public void Resize(int newRows, int newCols)
    {
        if (newRows <= 0 || newCols <= 0)
        {
            throw new ArgumentException("Matrix dimensions must be positive.");
        }

        short[,] newElements = new short[newRows, newCols];

        // Copying old elements to the new matrix and filling new ones with zeros
        for (int i = 0; i < Math.Min(rows, newRows); i++)
        {
            for (int j = 0; j < Math.Min(cols, newCols); j++)
            {
                newElements[i, j] = elements[i, j];
            }
        }

        elements = newElements;

        // Updating dimensions
        rows = newRows;
        cols = newCols;
    }

    // Explicit conversion from short to Matrix
    public static explicit operator Matrix(short value)
    {
        Matrix matrix = new Matrix(1, 1);
        matrix.elements[0, 0] = value;
        return matrix;
    }

    // Explicit conversion from Matrix to double for calculating the average
    public static explicit operator double(Matrix matrix)
    {
        return matrix.Average();
    }
}

class Program
{
    static void Main(string[] args)
    {
        Matrix matrix;

        // Requesting matrix dimensions from the user
        int rows, cols;

        while (true)
        {
            Console.Write("Enter number of rows for the matrix: ");
            if (int.TryParse(Console.ReadLine(), out rows) && rows > 0)
                break;
            Console.WriteLine("Error: please enter a positive integer.");
        }

        while (true)
        {
            Console.Write("Enter number of columns for the matrix: ");
            if (int.TryParse(Console.ReadLine(), out cols) && cols > 0)
                break;
            Console.WriteLine("Error: please enter a positive integer.");
        }

        // Creating an empty matrix and filling it with values from the user
        matrix = new Matrix(rows, cols);
        matrix.FillMatrix();

        var commands = new Dictionary<string, string>()
       {
           { "exit", "exit the program" },
           { "reset", "resets the matrix to zeros" },
           { "resize", "resizes the matrix" },
           { "edit", "edit the matrix" },
           { "short", "convert short to matrix" },
           { "aver", "get average of the matrix" },
           { "help", "get this manual" },
           { "display", "display the current matrix" }, // New command to display the matrix
           { "clear", "clear the screen" }              // New command to clear screen
       };

        while (true)
        {
            Console.WriteLine("\nEnter a command ('help' for command list):");
            string command = Console.ReadLine().ToLower();

            switch (command)
            {
                case "exit":
                    return;

                case "help":
                    foreach (var cmd in commands)
                    {
                        Console.WriteLine($"{cmd.Key}: {cmd.Value}");
                    }
                    break;

                case "reset":
                    if (matrix != null)
                        matrix.Reset(); // Fill with zeros
                    else
                        Console.WriteLine("First create a matrix.");
                    break;

                case "resize":
                    if (matrix != null)
                        ResizeMatrix(matrix);
                    else
                        Console.WriteLine("First create a matrix.");
                    break;

                case "edit":
                    if (matrix != null)
                        ChangeMatrixElement(matrix);
                    else
                        Console.WriteLine("First create a matrix.");
                    break;

                case "short":
                    Console.Write("Enter a short value to create a matrix: ");
                    if (short.TryParse(Console.ReadLine(), out short value))
                    {
                        matrix = (Matrix)value; // Explicit conversion from short to Matrix
                        Console.WriteLine("Matrix created from short value.");
                    }
                    else
                    {
                        Console.WriteLine("Error: please enter a valid short integer.");
                    }
                    break;

                case "aver":
                    if (matrix != null)
                        CalculateAverage(matrix);
                    else
                        Console.WriteLine("First create a matrix.");
                    break;

                case "display": // Handling display command
                    if (matrix != null)
                        matrix.Display();
                    else
                        Console.WriteLine("First create a matrix.");
                    break;

                case "clear": // Handling clear command
                    Console.Clear();
                    break;

                default:
                    if (!string.IsNullOrWhiteSpace(command))
                        Console.WriteLine("Error: select a valid menu item or enter 'help' for assistance.");
                    break;
            }
        }
    }

    static void ResizeMatrix(Matrix matrix)
    {
        int newRows, newCols;

        while (true)
        {
            Console.Write("Enter new number of rows: ");
            if (int.TryParse(Console.ReadLine(), out newRows) && newRows > 0)
                break;
            Console.WriteLine("Error: please enter a positive integer.");
        }

        while (true)
        {
            Console.Write("Enter new number of columns: ");
            if (int.TryParse(Console.ReadLine(), out newCols) && newCols > 0)
                break;
            Console.WriteLine("Error: please enter a positive integer.");
        }

        matrix.Resize(newRows, newCols);
    }

    static void ChangeMatrixElement(Matrix matrix)
    {
        int row, col;

        while (true)
        {
            Console.Write("Enter row index to change: ");
            if (int.TryParse(Console.ReadLine(), out row) && row >= 0 && row < matrix.Rows)
                break;
            Console.WriteLine($"Error: enter a valid row index from 0 to {matrix.Rows - 1}.");
        }

        while (true)
        {
            Console.Write("Enter column index to change: ");
            if (int.TryParse(Console.ReadLine(), out col) && col >= 0 && col < matrix.Cols)
                break;
            Console.WriteLine($"Error: enter a valid column index from 0 to {matrix.Cols - 1}.");
        }

        short newValue;

        while (true)
        {
            Console.Write($"Enter new value for element [{row}, {col}]: ");
            if (short.TryParse(Console.ReadLine(), out newValue))
                break;
            else
                Console.WriteLine("Error: please enter a valid short integer.");
        }

        matrix[row, col] = newValue;
    }

    static void CalculateAverage(Matrix matrix)
    {
        double average = (double)matrix; // Explicit conversion from Matrix to double for average calculation
        Console.WriteLine($"Average of the elements in the matrix: {average}");
    }
}
