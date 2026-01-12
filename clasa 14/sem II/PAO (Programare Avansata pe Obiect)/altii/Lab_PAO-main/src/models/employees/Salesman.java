package models.employees;

import database.EmbeddedDatabaseService;

import java.sql.PreparedStatement;
import java.sql.SQLException;

public class Salesman extends Employee{

    private int saleNumber = 0; // number of sales a salesman has made
    public Salesman(double salary, String firstName, String lastName) {
        super(salary, firstName, lastName);
    }

    public Salesman(double salary, String firstName, String lastName, String managerId) {
        super(salary, firstName, lastName, managerId);
    }

    public Salesman(String id, double salary, String firstName, String lastName, String managerId, int saleNumber){
        super(id, salary, firstName, lastName, managerId);
        this.saleNumber = saleNumber;
    }

    @Override
    void giveRaise() {
        this.salary = this.salary * 1.07;
    }

    @Override
    public String toString() {
        return super.toString() + " and occupies the position of salesman with " + this.saleNumber + " total sales.";
    }

    @Override
    public void saveToDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("insert into salesman(id, lastName, firstName, managerId, salary, saleNr) values(?,?,?,?,?,?)");
        statement.setString(1, this.getId());
        statement.setString(2, this.lastName);
        statement.setString(3, this.firstName);
        statement.setString(4, this.managerId);
        statement.setString(5, Double.toString(this.getSalary()));
        statement.setString(6, Integer.toString(this.saleNumber));

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void updateInDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("update salesman set lastName=?, firstName=?, managerId=?, salary=?, saleNr=? where id=?");

        statement.setString(6, this.getId());
        statement.setString(1, this.lastName);
        statement.setString(2, this.firstName);
        statement.setString(3, this.managerId);
        statement.setString(4, Double.toString(this.getSalary()));
        statement.setString(5, Integer.toString(this.saleNumber));

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void deleteFromDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("delete from salesman where id=?");

        statement.setString(1, this.getId());

        EmbeddedDatabaseService.runUpdate(statement);
    }
}
