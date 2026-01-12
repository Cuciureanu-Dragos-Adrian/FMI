package models.accounts;

import services.CustomerService;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class CreditAccount extends Account{
    protected float amountInDepth;

    public CreditAccount(int id, String bank, float amount, String currency, int customerId, float amountInDepth){
        super(id, bank, amount, currency, customerId);
        this.amountInDepth = amountInDepth;
    }

    public CreditAccount(Scanner sc){
        super(sc);

        System.out.println("Amount in depth: ");
        this.amountInDepth = Float.parseFloat(sc.nextLine());
    }

    public CreditAccount(ResultSet rs) throws SQLException {
        super(rs);
        this.amountInDepth = rs.getFloat(6);
    }

    public CreditAccount(CreditAccount creditAccount, CreditAccount newCreditAccount){
        super(creditAccount, newCreditAccount);
        this.amountInDepth = newCreditAccount.getAmountInDepth();
    }


    public float getAmountInDepth(){
        return amountInDepth;
    }

    public void setAmountInDepth(float amountInDepth){
        this.amountInDepth = amountInDepth;
    }


    @Override
    public String toString() {
        try {
            return super.toString() + String.format("amount in depth: %f %s \nreal balance: %f %s \ncard type: credit\n\nOwner: ",
                    getAmountInDepth(), getCurrency(), realBalance(), getCurrency())
                    + CustomerService.getInstance().get(getCustomerId());
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }


    public float realBalance(){
        return getAmount() - getAmountInDepth();
    }
}
