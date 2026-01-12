package models.clients;

import database.EmbeddedDatabaseService;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PF extends Client{
    private final String PNC; // PNC = personal numeric code
    private final String firstName;
    private final String lastName;
    public PF(String firstName, String lastName, String PNC, double funds) {
        super(funds);
        this.firstName = firstName;
        this.lastName = lastName;
        this.PNC = PNC;
    }
    public PF(String id, String firstName, String lastName, String PNC, double funds) {
        super(id, funds);
        this.firstName = firstName;
        this.lastName = lastName;
        this.PNC = PNC;
    }
    @Override
    public int getVAT() {
        return 24;
    }
    @Override
    public String toString() {
        return "Person " + this.lastName + " " + this.firstName + " #"+ this.PNC + "\n" + super.toString();
    }
    @Override
    public String getFullName() {
        return this.lastName + " " + this.firstName;
    }

    @Override
    public void saveToDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("insert into pf(id, lastName, firstName, pnc, funds) values(?,?,?,?,?)");
        statement.setString(1, this.getId());
        statement.setString(2, this.lastName);
        statement.setString(3, this.firstName);
        statement.setString(4, this.PNC);
        statement.setString(5, Double.toString(this.getFunds()));

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void updateInDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("update pf set lastName=?, firstName=?, pnc=?, funds=? where id=?");

        statement.setString(5, this.getId());
        statement.setString(1, this.lastName);
        statement.setString(2, this.firstName);
        statement.setString(3, this.PNC);
        statement.setString(4, Double.toString(this.getFunds()));

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void deleteFromDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("delete from pf where id=?");

        statement.setString(1, this.getId());

        EmbeddedDatabaseService.runUpdate(statement);
    }
}
