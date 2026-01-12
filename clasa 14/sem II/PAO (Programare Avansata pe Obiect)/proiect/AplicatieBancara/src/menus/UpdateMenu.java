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

public class UpdateMenu {
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
        System.out.println("\nUpdate:");

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
                    var manager = ManagerService.getInstance().get(id);
                    var newManager = new Manager(sc);
                    ManagerService.getInstance().update(new Manager(manager, newManager));
                    AuditService.writeLogInAudit("update manager");
                }
                case "2", "banker"   -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var banker = BankerService.getInstance().get(id);
                    var newBanker = new Banker(sc);
                    BankerService.getInstance().update(new Banker(banker, newBanker));
                    AuditService.writeLogInAudit("update banker");
                }
                case "3", "customer" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var customer = CustomerService.getInstance().get(id);
                    var newCustomer = new Customer(sc);
                    CustomerService.getInstance().update(new Customer(customer, newCustomer));
                    AuditService.writeLogInAudit("update customer");
                }
                case "4", "credit" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var creditAccount = CreditAccountService.getInstance().get(id);
                    var newCreditAccount = new CreditAccount(sc);
                    CreditAccountService.getInstance().update(new CreditAccount(creditAccount, newCreditAccount));
                    AuditService.writeLogInAudit("update credit account");
                }
                case "5", "debit" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var debitAccount = DebitAccountService.getInstance().get(id);
                    var newDebitAccount = new DebitAccount(sc);
                    DebitAccountService.getInstance().update(new DebitAccount(debitAccount, newDebitAccount));
                    AuditService.writeLogInAudit("update debit account");
                }
                case "6", "transaction" -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var transaction = TransactionService.getInstance().get(id);
                    var newTransaction = new Transaction(sc);
                    TransactionService.getInstance().update(new Transaction(transaction, newTransaction));
                    AuditService.writeLogInAudit("update transaction");
                }
                case "7", "back" -> run = false;
                default -> System.out.println("Wrong input!");
            }
        }
    }
}
