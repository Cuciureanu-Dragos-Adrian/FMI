package services;

public class MenuConstants {
    public static final String mainOptions = "\nPlease insert an option number:\n\n1. Read\n2. Print\n3. Delete\n4. System operations\n5. Stop the application.\n";
    public static final int[] mainBounds = new int[]{1, 5};
    public static final String readOptions = "\nWhat do you want to read?\n\n1. A client\n2. An employee\n3. A product\n4. Back.\n";
    public static final int[] readBounds = new int[]{1, 4};
    public static final String writeOptions = "\nWhat do you want to print?\n\n1. All clients\n2. All employees\n3. All products\n4. All collections.\n5. Back\n";
    public static final int[] writeBounds = new int[]{1, 5};
    public static final String deleteOptions = "\nWhat do you want to delete?\n\n1. A client\n2. An employee\n3. A product\n4. Back.\n";
    public static final int[] deleteBounds = new int[]{1, 4};

    public static final String operationOptions = """
            Choose an operation:

            1. Assign a manager to an employee
            2. Print direct subordinates of an employee
            3. Print all subordinates of an employee
            4. Print all bosses
            5. Print the employee with the max salary
            6. Adjust a product's stock
            7. Set a discount for a product.
            8. Print the product with the highest stock
            9. Print products ordered by price in descending order
            10. Print products ordered by discount in ascending order
            11. Make a client purchase a product.
            12. Back.
            """;

    public static final int[] operationBounds = new int[]{1, 12};

}
