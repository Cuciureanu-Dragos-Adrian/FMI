package models.accounts;

import services.CustomerService;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class DebitAccount extends Account{
    protected float interestRate;

    public DebitAccount(int id, String bank, float amount, String currency, int customerId, float interestRate){
        super(id, bank, amount, currency, customerId);
        this.interestRate = interestRate;
    }

    public DebitAccount(Scanner sc){
        super(sc);

        System.out.println("Interest rate: ");
        this.interestRate = Float.parseFloat(sc.nextLine());
    }

    public DebitAccount(ResultSet rs) throws SQLException {
        super(rs);
        this.interestRate = rs.getFloat(6);
    }

    public DebitAccount(DebitAccount creditAccount, DebitAccount newCreditAccount){
        super(creditAccount, newCreditAccount);
        this.interestRate = newCreditAccount.getInterestRate();
    }


    public float getInterestRate(){
        return interestRate;
    }

    public void setInterestRate(float interestRate){
        this.interestRate = interestRate;
    }


    @Override
    public String toString() {
        try {
            return super.toString() + String.format("interest rate: %f \ncard type: debit\n\nOwner: ",
                    getInterestRate()) + CustomerService.getInstance().get(getCustomerId());
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

    }


    public void increaseAmountByInterestRate(){
        amount *= ((interestRate + 100) / 100);
    }
}
