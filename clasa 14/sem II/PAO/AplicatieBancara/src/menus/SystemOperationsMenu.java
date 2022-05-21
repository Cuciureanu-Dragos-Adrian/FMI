package menus;

import services.*;

import java.sql.SQLException;
import java.util.*;

public class SystemOperationsMenu {
    static Map<String, String> options = new LinkedHashMap<>();

    private static void createOptions() {
        options.clear();

        options.put("1", "Raise a manager salary");
        options.put("2", "Raise all managers salary");
        options.put("3", "Decrease a manager salary");
        options.put("4", "Decrease all managers salary");
        options.put("5", "Sort all managers by salary ascending");
        options.put("6", "Sort all managers by salary descending");
        options.put("7", "Sort all managers by total salary ascending");
        options.put("8", "Sort all managers by total salary descending");
        options.put("9", "Raise a banker salary");
        options.put("10", "Raise all bankers salary");
        options.put("11", "Decrease a banker salary");
        options.put("12", "Decrease all bankers salary");
        options.put("13", "Sort all bankers by salary ascending");
        options.put("14", "Sort all bankers by salary descending");
        options.put("15", "Sort all bankers by total salary ascending");
        options.put("16", "Sort all bankers by total salary descending");
        options.put("17", "Get a customer's credit accounts");
        options.put("18", "Get a customer's debit accounts");
        options.put("19", "Get all customers' credit accounts");
        options.put("20", "Get all customers' debit accounts");
        options.put("21", "Add the interest on a debit account's amount");
        options.put("22", "Add the interest on all debit accounts' amount");
        options.put("23", "Confirm a transaction");
        options.put("24", "Confirm all transactions");
        options.put("25/back", "Back");
    }

    private static void showOptions() {
        System.out.println("\nSystem operations:");

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
                case "1"  -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var manager = ManagerService.getInstance().get(id);
                    manager.raiseSalary();
                    ManagerService.getInstance().update(manager);
                    AuditService.writeLogInAudit("raise a manager salary");
                }
                case "2"  -> {
                    var managers = ManagerService.getInstance().getAll();
                    for (var manager : managers){
                        manager.raiseSalary();
                        ManagerService.getInstance().update(manager);
                    }
                    AuditService.writeLogInAudit("raise all managers salary");
                }
                case "3"  -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var manager = ManagerService.getInstance().get(id);
                    manager.decreaseSalary();
                    ManagerService.getInstance().update(manager);
                    AuditService.writeLogInAudit("decrease a manager salary");
                }
                case "4"  -> {
                    var managers = ManagerService.getInstance().getAll();
                    for (var manager : managers){
                        manager.decreaseSalary();
                        ManagerService.getInstance().update(manager);
                    }
                    AuditService.writeLogInAudit("decrease all managers salary");
                }
                case "5"  -> {
                    ManagerService.getInstance().getAllAsc().forEach(System.out::println);
                    AuditService.writeLogInAudit("sort all managers by salary ascending");
                }
                case "6"  -> {
                    ManagerService.getInstance().getAllDesc().forEach(System.out::println);
                    AuditService.writeLogInAudit("sort all managers by salary descending");
                }
                case "7"  -> {
                    var managers = ManagerService.getInstance().getAll();
                    Collections.sort(managers);
                    Collections.reverse(managers);
                    managers.forEach(System.out::println);
                    AuditService.writeLogInAudit("sort all managers by total salary ascending");
                }
                case "8"  -> {
                    var managers = ManagerService.getInstance().getAll();
                    Collections.sort(managers);
                    managers.forEach(System.out::println);
                    AuditService.writeLogInAudit("sort all managers by total salary descending");
                }
                case "9"  -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var banker = BankerService.getInstance().get(id);
                    banker.raiseSalary();
                    BankerService.getInstance().update(banker);
                    AuditService.writeLogInAudit("raise a banker salary");
                }
                case "10"  -> {
                    var bankers = BankerService.getInstance().getAll();
                    for (var banker : bankers){
                        banker.raiseSalary();
                        BankerService.getInstance().update(banker);
                    }
                    AuditService.writeLogInAudit("raise all bankers salary");
                }
                case "11"  -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var banker = BankerService.getInstance().get(id);
                    banker.decreaseSalary();
                    BankerService.getInstance().update(banker);
                    AuditService.writeLogInAudit("decrease a banker salary");
                }
                case "12"  -> {
                    var bankers = BankerService.getInstance().getAll();
                    for (var banker : bankers){
                        banker.raiseSalary();
                        BankerService.getInstance().update(banker);
                    }
                    AuditService.writeLogInAudit("decrease all bankers salary");
                }
                case "13"  -> {
                    BankerService.getInstance().getAllAsc().forEach(System.out::println);
                    AuditService.writeLogInAudit("sort all bankers by salary ascending");
                }
                case "14"  -> {
                    BankerService.getInstance().getAllDesc().forEach(System.out::println);
                    AuditService.writeLogInAudit("sort all bankers by salary descending");
                }
                case "15"  -> {
                    var bankers = BankerService.getInstance().getAll();
                    Collections.sort(bankers);
                    Collections.reverse(bankers);
                    bankers.forEach(System.out::println);
                    AuditService.writeLogInAudit("sort all bankers by total salary ascending");
                }
                case "16"  -> {
                    var bankers = BankerService.getInstance().getAll();
                    Collections.sort(bankers);
                    bankers.forEach(System.out::println);
                    AuditService.writeLogInAudit("sort all bankers by total salary descending");
                }
                case "17"  -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    CustomerService.getInstance().getCreditAccountOfCustomer(id).forEach(System.out::println);
                    AuditService.writeLogInAudit("get a customer's credit accounts");
                }
                case "18"  -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    CustomerService.getInstance().getDebitAccountOfCustomer(id).forEach(System.out::println);
                    AuditService.writeLogInAudit("get a customer's debit accounts");
                }
                case "19"  -> {
                    var customers = CustomerService.getInstance().getAll();
                    for (var customer : customers){
                        CustomerService.getInstance().getCreditAccountOfCustomer(customer.getId()).forEach(System.out::println);
                    }
                    AuditService.writeLogInAudit("get all customers' credit accounts");
                }
                case "20"  -> {
                    var customers = CustomerService.getInstance().getAll();
                    for (var customer : customers){
                        CustomerService.getInstance().getDebitAccountOfCustomer(customer.getId()).forEach(System.out::println);
                    }
                    AuditService.writeLogInAudit("get all customers' debit accounts");
                }
                case "21"  -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var debitAccount = DebitAccountService.getInstance().get(id);
                    debitAccount.increaseAmountByInterestRate();
                    DebitAccountService.getInstance().update(debitAccount);
                    AuditService.writeLogInAudit("add the interest on a debit account's amount");
                }
                case "22"  -> {
                    var debitAccounts = DebitAccountService.getInstance().getAll();
                    for (var debitAccount : debitAccounts){
                        debitAccount.increaseAmountByInterestRate();
                        DebitAccountService.getInstance().update(debitAccount);
                    }
                    AuditService.writeLogInAudit("add the interest on all debit accounts' amount");
                }
                case "23"  -> {
                    System.out.println("Enter ID:");
                    int id = Integer.parseInt(sc.nextLine());
                    var transaction = TransactionService.getInstance().get(id);

                    var sender = CreditAccountService.getInstance().get(transaction.getSenderId());
                    sender.setAmountInDepth(sender.getAmountInDepth() + transaction.getAmount());

                    var receiver = CreditAccountService.getInstance().get(transaction.getReceiverId());
                    receiver.setAmount(receiver.getAmount() + transaction.getAmount() * (100 - transaction.getCommission()) / 100);

                    CreditAccountService.getInstance().update(sender);
                    CreditAccountService.getInstance().update(receiver);

                    AuditService.writeLogInAudit("confirm a transaction");
                }
                case "24"  -> {
                    var transactions = TransactionService.getInstance().getAll();
                    for (var transaction : transactions){
                        var sender = CreditAccountService.getInstance().get(transaction.getSenderId());
                        sender.setAmountInDepth(sender.getAmountInDepth() + transaction.getAmount());

                        var receiver = CreditAccountService.getInstance().get(transaction.getReceiverId());
                        receiver.setAmount(receiver.getAmount() + transaction.getAmount() * (100 - transaction.getCommission()) / 100);

                        CreditAccountService.getInstance().update(sender);
                        CreditAccountService.getInstance().update(receiver);
                    }
                    AuditService.writeLogInAudit("confirm all transactions");
                }
                case "25", "back"  -> run = false;
                default -> System.out.println("Wrong input!");
            }
        }
    }
}
