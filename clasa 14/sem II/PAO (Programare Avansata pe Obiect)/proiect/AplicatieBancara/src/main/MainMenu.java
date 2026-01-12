package main;

import menus.*;

import java.sql.SQLException;
import java.util.*;

public class MainMenu {
    static Map<String, String> options = new LinkedHashMap<>();

    private static void createOptions() {
        options.clear();

        options.put("1", "Create");
        options.put("2", "Read");
        options.put("3", "Update");
        options.put("4", "Delete");
        options.put("5", "System operations");
        options.put("6", "Exit");
    }

    private static void showOptions() {
        System.out.println("\nOptions:");

        for (Map.Entry<String,String> option : options.entrySet()){
            System.out.println(option.getKey() + ". " + option.getValue());
        }
    }

    public static void menu(Scanner sc) throws SQLException, Exception {
        boolean run = true;
        createOptions();

        System.out.println("Welcome to my Banking Application");

        while(run) {
            showOptions();
            System.out.println("\nChoose your option:");
            String action = sc.nextLine().toLowerCase();

            switch (action) {
                case "1", "create" -> CreateMenu.menu(sc);
                case "2", "read"   -> ReadMenu.menu(sc);
                case "3", "update" -> UpdateMenu.menu(sc);
                case "4", "delete" -> DeleteMenu.menu(sc);
                case "5", "system" -> SystemOperationsMenu.menu(sc);
                case "6", "exit"   -> run = false;
                default -> System.out.println("Wrong input!");
            }
        }
    }
}
