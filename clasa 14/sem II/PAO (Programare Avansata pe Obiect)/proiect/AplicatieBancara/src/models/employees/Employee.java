package models.employees;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public abstract class Employee {
    private final int id;
    protected float salary;
    protected final String firstName;
    protected final String lastName;

    public Employee(int id, float salary, String firstName, String lastName){
        this.id = id;
        this.salary = salary;
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public Employee(Scanner sc){
        this.id = 0;

        System.out.println("\nSalary: ");
        this.salary = Float.parseFloat(sc.nextLine());

        System.out.println("First name: ");
        this.firstName = sc.nextLine();

        System.out.println("Last name: ");
        this.lastName = sc.nextLine();
    }

    public Employee(ResultSet rs) throws SQLException {
        this.id = rs.getInt(1);
        this.salary = rs.getFloat(2);
        this.firstName = rs.getString(3);
        this.lastName = rs.getString(4);
    }

    public Employee(Employee employee, Employee newEmployee){
        this.id = employee.getId();
        this.salary = newEmployee.getSalary();
        this.firstName = newEmployee.getFirstName();
        this.lastName = newEmployee.getLastName();
    }


    public int getId(){
        return id;
    }

    public float getSalary(){
        return salary;
    }

    public void setSalary(float salary){
        this.salary = salary;
    }

    public String getFirstName(){
        return firstName;
    }

    public String getLastName(){
        return lastName;
    }

    @Override
    public String toString() {
        return String.format("\nEmployee \nid: %d \nfirst name: %s \nlast name: %s \nsalary: %f\n",
                getId(), getFirstName(), getLastName(), getSalary());
    }


    abstract float totalAnnualSalary();
    abstract void raiseSalary();
    abstract void decreaseSalary();
}
