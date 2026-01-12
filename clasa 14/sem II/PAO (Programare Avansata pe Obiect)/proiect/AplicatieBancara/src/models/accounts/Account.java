package models.accounts;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public abstract class Account {
    private final int id;
    protected final String bank;
    protected float amount;
    protected final String currency;
    protected int customerId;

    public Account(int id, String bank, float amount, String currency, int customerId){
        this.id = id;
        this.bank = bank;
        this.amount = amount;
        this.currency = currency;
        this.customerId = customerId;
    }

    public Account(Scanner sc){
        this.id = 0;

        System.out.println("\nBank: ");
        this.bank = sc.nextLine();

        System.out.println("Amount: ");
        this.amount = Float.parseFloat(sc.nextLine());

        System.out.println("Currency: ");
        this.currency = sc.nextLine();

        System.out.println("Customer ID: ");
        this.customerId = Integer.parseInt(sc.nextLine());
    }

    public Account(ResultSet rs) throws SQLException {
        this.id = rs.getInt(1);
        this.bank = rs.getString(2);
        this.amount = rs.getFloat(3);
        this.currency = rs.getString(4);
        this.customerId = rs.getInt(5);
    }

    public Account(Account account, Account newAccount){
        this.id = account.getId();
        this.bank = newAccount.getBank();
        this.amount = newAccount.getAmount();
        this.currency = newAccount.getCurrency();
        this.customerId = newAccount.getCustomerId();
    }


    public int getId(){
        return id;
    }

    public float getAmount(){
        return amount;
    }

    public void setAmount(float amount){
        this.amount = amount;
    }

    public String getCurrency(){
        return currency;
    }

    public String getBank(){
        return bank;
    }

    public int getCustomerId() {
        return customerId;
    }

    public void setCustomerId(int customerId){
        this.customerId = customerId;
    }


    @Override
    public String toString() {
        return String.format("\nAccount \nid: %d \namount: %f %s \nbank: %s\n",
                getId(), getAmount(), getCurrency(), getBank());
    }
}
