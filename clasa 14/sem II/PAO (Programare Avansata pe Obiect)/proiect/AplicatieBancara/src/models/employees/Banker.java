package models.employees;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class Banker extends Employee implements Comparable<Banker>{
    protected float workedFreeDays;

    public Banker(int id, float salary, String firstName, String lastName, float workedFreeDays){
        super(id, salary, firstName, lastName);
        this.workedFreeDays = workedFreeDays;
    }

    public Banker(Scanner sc){
        super(sc);

        System.out.println("Worked free days: ");
        this.workedFreeDays = Float.parseFloat(sc.nextLine());
    }

    public Banker(ResultSet rs) throws SQLException {
        super(rs);
        this.workedFreeDays = rs.getFloat(5);
    }

    public Banker(Banker banker, Banker newBanker){
        super(banker, newBanker);
        this.workedFreeDays = newBanker.getWorkedFreeDays();
    }


    public float getWorkedFreeDays(){
        return workedFreeDays;
    }

    public void setWorkedFreeDays(float workedFreeDays){
        this.workedFreeDays = workedFreeDays;
    }


    @Override
    public String toString() {
        return super.toString() + String.format("worked free days: %f \ntotal annual salary: %f \nrole: manager\n",
                getWorkedFreeDays(), totalAnnualSalary());
    }


    @Override
    public int compareTo(Banker banker){
        return Float.compare(banker.totalAnnualSalary(), this.totalAnnualSalary());
    }


    public float totalAnnualSalary(){
        return salary * 12 * (workedFreeDays + 250) / 250;
    }

    public void raiseSalary(){
        salary *= 1.1;
    }

    public void decreaseSalary(){
        salary *= 0.9;
    }
}
