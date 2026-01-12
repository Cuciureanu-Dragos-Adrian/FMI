package menus;

import services.*;

import java.sql.SQLException;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Scanner;

public class ReadMenu {
    static Map<String, String> options = new LinkedHashMap<>();

    private static void createOptions() {
        options.clear();

        options.put("1/manager", "A manager");
        options.put("2/managers", "All managers");
        options.put("3/banker", "A banker");
        options.put("4/bankers", "All bankers");
        options.put("5/customer", "A customer");
        options.put("6/customers", "All customers");
        options.put("7/credit", "A credit account");
        options.put("8/credits", "All credit accounts");
        options.put("9/debit", "A debit account");
        options.put("10/debits", "All debit accounts");
        options.put("11/transaction", "A transaction");
        options.put("12/transactions", "All transactions");
        options.put("13/back", "Back");
    }

    private static void showOptions() {
        System.out.println("\nRead:");

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
                case "1", "manager" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var manager = ManagerService.getInstance().get(id);
                    System.out.println(manager);
                    AuditService.writeLogInAudit("read manager");
                }
                case "2", "managers" -> {
                    ManagerService.getInstance().getAll().forEach(System.out::println);
                    AuditService.writeLogInAudit("read all managers");
                }
                case "3", "banker" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var banker = BankerService.getInstance().get(id);
                    System.out.println(banker);
                    AuditService.writeLogInAudit("read banker");
                }
                case "4", "bankers" -> {
                    BankerService.getInstance().getAll().forEach(System.out::println);
                    AuditService.writeLogInAudit("read all banker");
                }
                case "5", "customer" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var customer = CustomerService.getInstance().get(id);
                    System.out.println(customer);
                    AuditService.writeLogInAudit("read customer");
                }
                case "6", "customers" -> {
                    CustomerService.getInstance().getAll().forEach(System.out::println);
                    AuditService.writeLogInAudit("read all customer");
                }
                case "7", "credit" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var creditAccount = CreditAccountService.getInstance().get(id);
                    System.out.println(creditAccount);
                    AuditService.writeLogInAudit("read credit account");
                }
                case "8", "credits" -> {
                    CreditAccountService.getInstance().getAll().forEach(System.out::println);
                    AuditService.writeLogInAudit("read all credit account");
                }
                case "9", "debit" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var debitAccount = DebitAccountService.getInstance().get(id);
                    System.out.println(debitAccount);
                    AuditService.writeLogInAudit("read debit account");
                }
                case "10", "debits" -> {
                    DebitAccountService.getInstance().getAll().forEach(System.out::println);
                    AuditService.writeLogInAudit("read all debit account");
                }
                case "11", "transaction" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var transaction = TransactionService.getInstance().get(id);
                    System.out.println(transaction);
                    AuditService.writeLogInAudit("read transaction");
                }
                case "12", "transactions" -> {
                    TransactionService.getInstance().getAll().forEach(System.out::println);
                    AuditService.writeLogInAudit("read all transactions");
                }
                case "13", "back" -> run = false;
                default -> System.out.println("Wrong input!");
            }
        }
    }
}
