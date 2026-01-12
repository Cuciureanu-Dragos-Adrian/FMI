package models.clients;

import database.EmbeddedDatabaseService;

import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PJ extends Client{
    private final String FIC; //fiscal identification code
    private final String name;

    public PJ(String name, String FIC, double funds) {
        super(funds);
        this.name = name;
        this.FIC = FIC;
    }
    public PJ(String id, String name, String FIC, double funds) {
        super(id, funds);
        this.name = name;
        this.FIC = FIC;
    }

    @Override
    public int getVAT() {
        return 0;
    }

    @Override
    public String toString() {
        return "Business " + this.name + " #" + this.FIC + "\n" + super.toString();
    }

    @Override
    public String getFullName() {
        return this.name;
    }

    @Override
    public void saveToDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("insert into pj(id, name, fic, funds) values(?,?,?,?)");
        statement.setString(1, this.getId());
        statement.setString(2, this.name);
        statement.setString(3, this.FIC);
        statement.setString(4, Double.toString(this.getFunds()));

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void updateInDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("update pj set name=?, fic=?, funds=? where id=?");

        statement.setString(4, this.getId());
        statement.setString(1, this.name);
        statement.setString(2, this.FIC);
        statement.setString(3, Double.toString(this.getFunds()));

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void deleteFromDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("delete from pj where id=?");

        statement.setString(1, this.getId());

        EmbeddedDatabaseService.runUpdate(statement);
    }
}
