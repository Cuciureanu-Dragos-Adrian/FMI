package services;

import database.EmbeddedDatabaseService;

import java.util.Scanner;

public class MenuService {
    private static final Scanner scanner = new Scanner(System.in);
    private static String currentOptions = MenuConstants.mainOptions; //string of current options
    private static int[] currentBounds = MenuConstants.mainBounds; //clamp of option numbers: bounds[0] = the lower bound, bounds[1] = upper bound
    private static boolean run = true;
    public static void runMenu() throws Exception {
        while (run) {
            System.out.print(currentOptions);
            //read input and strip spaces

            //get a valid choice
            int choice = Utilities.readIntInInterval(scanner, currentBounds[0], currentBounds[1]);

            switch (currentOptions) {
                case MenuConstants.mainOptions -> mainOptions(choice);
                case MenuConstants.readOptions -> readOptions(choice);
                case MenuConstants.writeOptions -> writeOptions(choice);
                case MenuConstants.deleteOptions -> deleteOptions(choice);
                case MenuConstants.operationOptions -> operationOptions(choice);
            }

        }
    }

    public static void mainOptions(int choice){
        switch(choice){
            case 1:
                currentOptions = MenuConstants.readOptions;
                currentBounds = MenuConstants.readBounds;
                break;
            case 2:
                currentOptions = MenuConstants.writeOptions;
                currentBounds = MenuConstants.writeBounds;
                break;
            case 3:
                currentOptions = MenuConstants.deleteOptions;
                currentBounds = MenuConstants.deleteBounds;
                break;
            case 4:
                currentOptions = MenuConstants.operationOptions;
                currentBounds = MenuConstants.operationBounds;
                break;
            case 5:
                run = false;
                break;
        }
    }

    public static void readOptions(int choice) throws Exception {
        switch(choice){
            case 1 -> ClientService.readClient(scanner);
            case 2 -> EmployeeService.readEmployee(scanner);
            case 3 -> ProductService.readProduct(scanner);
        }
        currentBounds = MenuConstants.mainBounds;
        currentOptions = MenuConstants.mainOptions;
    }

    public static void writeOptions(int choice) throws Exception {
        switch (choice) {
            case 1 -> ClientService.printAllClients();
            case 2 -> EmployeeService.printAllEmployees();
            case 3 -> ProductService.printAllProducts();
            case 4 -> {
                ClientService.printAllClients();
                EmployeeService.printAllEmployees();
                ProductService.printAllProducts();
            }
        }
        currentBounds = MenuConstants.mainBounds;
        currentOptions = MenuConstants.mainOptions;
    }

    public static void deleteOptions(int choice) throws Exception {
        switch(choice){
            case 1 -> ClientService.deleteClient(scanner);
            case 2 -> EmployeeService.deleteEmployee(scanner);
            case 3 -> ProductService.deleteProduct(scanner);
        }
        currentBounds = MenuConstants.mainBounds;
        currentOptions = MenuConstants.mainOptions;
    }

    public static void operationOptions(int choice) throws Exception{
        switch(choice){
            case 1 -> EmployeeService.setManagerForEmployee(scanner);
            case 2 -> EmployeeService.printSubordinates(scanner, "direct");
            case 3 -> EmployeeService.printSubordinates(scanner, "all");
            case 4 -> EmployeeService.printBosses();
            case 5 -> EmployeeService.printEmployeeWithMaxSalary();
            case 6 -> ProductService.adjustStock(scanner);
            case 7 -> ProductService.createDiscount(scanner);
            case 8 -> ProductService.printMerchandiseWithHighestStock();
            case 9 -> ProductService.printProductsOrdered("price");
            case 10 -> ProductService.printProductsOrdered("discount");
            case 11 -> ClientService.executeSale(scanner);
        }
        currentBounds = MenuConstants.mainBounds;
        currentOptions = MenuConstants.mainOptions;
    }
}
