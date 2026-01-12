package models.customers;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class Customer {
    private final int id;
    protected final String firstName;
    protected final String lastName;
    protected final String email;


    public Customer(int id, String firstName, String lastName, String email){
        this.id = id;
        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
    }

    public Customer(Scanner sc){
        this.id = 0;

        System.out.println("\nFirst name: ");
        this.firstName = sc.nextLine();

        System.out.println("Last name: ");
        this.lastName = sc.nextLine();

        System.out.println("Email: ");
        this.email = sc.nextLine();
    }

    public Customer(ResultSet rs) throws SQLException {
        this.id = rs.getInt(1);
        this.firstName = rs.getString(2);
        this.lastName = rs.getString(3);
        this.email = rs.getString(4);
    }

    public Customer(Customer customer, Customer newCustomer){
        this.id = customer.getId();
        this.firstName = newCustomer.getFirstName();
        this.lastName = newCustomer.getLastName();
        this.email = newCustomer.getEmail();
    }


    public int getId(){
        return id;
    }

    public String getFirstName(){
        return firstName;
    }

    public String getLastName(){
        return lastName;
    }

    public String getEmail(){
        return email;
    }

    @Override
    public String toString() {
        return String.format("Customer \nid: %d \nfirst name: %s \nlast name: %s \nemail: %s\n",
                getId(), getFirstName(), getLastName(), getEmail());
    }
}
