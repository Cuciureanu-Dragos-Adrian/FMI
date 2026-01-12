package models.transactions;

import models.customers.Customer;
import services.CreditAccountService;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class Transaction {
    private final int id;
    protected int senderId;
    protected int receiverId;
    protected float amount;
    protected float commission;

    public Transaction(int id, int senderId, int receiverId, float amount, float commission){
        this.id = id;
        this.senderId = senderId;
        this.receiverId = receiverId;
        this.amount = amount;
        this.commission = commission;
    }

    public Transaction(Scanner sc){
        this.id = 0;

        System.out.println("ID of the credit account that sends the money: ");
        this.senderId = Integer.parseInt(sc.nextLine());

        System.out.println("ID of the credit account that receives the money: ");
        this.receiverId = Integer.parseInt(sc.nextLine());

        System.out.println("Amount: ");
        this.amount = Float.parseFloat(sc.nextLine());

        System.out.println("Commission: ");
        this.commission = Float.parseFloat(sc.nextLine());
    }

    public Transaction(ResultSet rs) throws SQLException {
        this.id = rs.getInt(1);
        this.senderId = rs.getInt(2);
        this.receiverId = rs.getInt(3);
        this.amount = rs.getFloat(4);
        this.commission = rs.getFloat(5);
    }

    public Transaction(Transaction transaction, Transaction newTransaction){
        this.id = transaction.getId();
        this.senderId = newTransaction.getSenderId();
        this.receiverId = newTransaction.getReceiverId();
        this.amount = newTransaction.getAmount();
        this.commission = newTransaction.getCommission();
    }


    public int getId(){
        return id;
    }

    public int getSenderId() {
        return senderId;
    }

    public void setSenderId(int senderId){
        this.senderId = senderId;
    }

    public int getReceiverId() {
        return receiverId;
    }

    public void setReceiverId(int receiverId){
        this.receiverId = receiverId;
    }

    public float getAmount(){
        return amount;
    }

    public void setAmount(float amount){
        this.amount = amount;
    }

    public float getCommission(){
        return commission;
    }

    public void setCommission(float commission){
        this.commission = commission;
    }


    @Override
    public String toString() {
        try {
            return String.format("\nTransaction \nid: %d \namount: %f \ncommission: %f",
                    getId(), getAmount(), getCommission()) +
                    "\n\nSending Credit Account: " + CreditAccountService.getInstance().get(senderId) +
                    "\n\nReceiving Credit Account: " + CreditAccountService.getInstance().get(receiverId);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
