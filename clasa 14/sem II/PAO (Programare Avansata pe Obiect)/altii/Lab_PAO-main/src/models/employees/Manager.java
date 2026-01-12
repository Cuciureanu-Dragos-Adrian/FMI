package models.employees;

import database.EmbeddedDatabaseService;

import java.sql.PreparedStatement;
import java.sql.SQLException;

public class Manager extends Employee {

    public Manager(double salary, String firstName, String lastName) {
        super(salary, firstName, lastName);
    }
    public Manager(double salary, String firstName, String lastName, String managerId){
        super(salary, firstName, lastName, managerId);
    }
    public Manager(String id, double salary, String firstName, String lastName, String managerId){
        super(id, salary, firstName, lastName, managerId);
    }
    public void giveRaise() {
        this.salary = this.salary * 1.15;
    }
    @Override
    public String toString() {
        return super.toString() + " and occupies the position of manager.";

    }

    @Override
    public void saveToDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("insert into manager(id, lastName, firstName, managerId, salary) values(?,?,?,?,?)");
        statement.setString(1, this.getId());
        statement.setString(2, this.lastName);
        statement.setString(3, this.firstName);
        statement.setString(4, this.managerId);
        statement.setString(5, Double.toString(this.getSalary()));

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void updateInDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("update manager set lastName=?, firstName=?, managerId=?, salary=? where id=?");

        statement.setString(5, this.getId());
        statement.setString(1, this.lastName);
        statement.setString(2, this.firstName);
        statement.setString(3, this.managerId);
        statement.setString(4, Double.toString(this.getSalary()));

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void deleteFromDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("delete from manager where id=?");

        statement.setString(1, this.getId());

        EmbeddedDatabaseService.runUpdate(statement);
    }
}
