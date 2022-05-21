package menus;

import services.*;

import java.sql.SQLException;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Scanner;

public class DeleteMenu {
    static Map<String, String> options = new LinkedHashMap<>();

    private static void createOptions() {
        options.clear();

        options.put("1/manager", "A manager");
        options.put("2/banker", "A banker");
        options.put("3/customer", "A customer");
        options.put("4/credit", "A credit account");
        options.put("5/debit", "A debit account");
        options.put("6/transaction", "A transaction");
        options.put("7/back", "Back");
    }

    private static void showOptions() {
        System.out.println("\nDelete:");

        for (Map.Entry<String,String> option : options.entrySet()){
            System.out.println(option.getKey() + ". " + option.getValue());
        }
    }

    public static void menu(Scanner sc) throws SQLException, Exception {
        boolean run = true;
        createOptions();

        while(run) {
            showOptions();
            System.out.println("\nChoose your option:");
            String action = sc.nextLine().toLowerCase();

            switch (action) {
                case "1", "manager"  -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    ManagerService.getInstance().delete(id);
                    AuditService.writeLogInAudit("delete manager");
                }
                case "2", "banker"   -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    BankerService.getInstance().delete(id);
                    AuditService.writeLogInAudit("delete banker");
                }
                case "3", "customer" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    CustomerService.getInstance().delete(id);
                    AuditService.writeLogInAudit("delete customer");
                }
                case "4", "credit" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    CreditAccountService.getInstance().delete(id);
                    AuditService.writeLogInAudit("delete credit account");
                }
                case "5", "debit" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    DebitAccountService.getInstance().delete(id);
                    AuditService.writeLogInAudit("delete debit account");
                }
                case "6", "transaction" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    TransactionService.getInstance().delete(id);
                    AuditService.writeLogInAudit("delete transaction");
                }
                case "7", "back"     -> run = false;
                default -> System.out.println("Wrong input!");
            }
        }
    }
}
