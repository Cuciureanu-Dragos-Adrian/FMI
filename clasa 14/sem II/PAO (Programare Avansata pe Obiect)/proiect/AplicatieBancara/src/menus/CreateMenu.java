package menus;

import models.accounts.CreditAccount;
import models.accounts.DebitAccount;
import models.customers.Customer;
import models.employees.Banker;
import models.employees.Manager;
import models.transactions.Transaction;
import services.*;

import java.sql.SQLException;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Scanner;

public class CreateMenu {
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
        System.out.println("\nCreate:");

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
                    ManagerService.getInstance().add(new Manager(sc));
                    AuditService.writeLogInAudit("create manager");
                }
                case "2", "banker" -> {
                    BankerService.getInstance().add(new Banker(sc));
                    AuditService.writeLogInAudit("create banker");
                }
                case "3", "customer" -> {
                    CustomerService.getInstance().add(new Customer(sc));
                    AuditService.writeLogInAudit("create customer");
                }
                case "4", "credit" -> {
                    CreditAccountService.getInstance().add(new CreditAccount(sc));
                    AuditService.writeLogInAudit("create credit account");
                }
                case "5", "debit" -> {
                    DebitAccountService.getInstance().add(new DebitAccount(sc));
                    AuditService.writeLogInAudit("create debit account");
                }
                case "6", "transaction" -> {
                    TransactionService.getInstance().add(new Transaction(sc));
                    AuditService.writeLogInAudit("create transaction");
                }
                case "7", "back" -> run = false;
                default -> System.out.println("Wrong input!");
            }
        }
    }
}
