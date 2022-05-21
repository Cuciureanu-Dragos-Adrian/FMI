package models.employees;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class Manager extends Employee implements Comparable<Manager>{
    protected float bonus;

    public Manager(int id, float salary, String firstName, String lastName, float bonus){
        super(id, salary, firstName, lastName);
        this.bonus = bonus;
    }

    public Manager(Scanner sc){
        super(sc);

        System.out.println("Bonus: ");
        this.bonus = Float.parseFloat(sc.nextLine());
    }

    public Manager(ResultSet rs) throws SQLException {
        super(rs);
        this.bonus = rs.getFloat(5);
    }

    public Manager(Manager manager, Manager newManager){
        super(manager, newManager);
        this.bonus = newManager.getBonus();
    }


    public float getBonus(){
        return bonus;
    }

    public void setBonus(float bonus){
        this.bonus = bonus;
    }


    @Override
    public String toString() {
        return super.toString() + String.format("bonus: %f \ntotal annual salary: %f \nrole: manager\n", getBonus(), totalAnnualSalary());

    }


    @Override
    public int compareTo(Manager manager){
        return Float.compare(manager.totalAnnualSalary(), this.totalAnnualSalary());
    }


    public float totalAnnualSalary(){
        return salary * 12 + bonus;
    }

    public void raiseSalary(){
        setSalary(getSalary() * (float)1.2);
    }

    public void decreaseSalary(){
        salary *= 0.85;
    }
}
