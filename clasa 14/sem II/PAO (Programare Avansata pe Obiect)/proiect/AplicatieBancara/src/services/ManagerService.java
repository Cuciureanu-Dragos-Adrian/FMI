package services;

import models.employees.Manager;
import utilities.jdbc.JDBCService;
import utilities.jdbc.JDBCServiceInterface;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

public class ManagerService implements JDBCServiceInterface<Manager> {
    private static ManagerService instance = null;

    public static ManagerService getInstance() {
        if (instance == null)
        {
            instance = new ManagerService();
        }
        return instance;
    }

    @Override
    public Manager get(int id) throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM managers WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(sql);
        prep.setInt(1, id);

        prep.execute();
        prep.getResultSet().next();

        return new Manager(prep.getResultSet());
    }

    @Override
    public List<Manager> getAll() throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM managers";

        ResultSet rs = jdbcService.getStatement().executeQuery(sql);
        var records = new ArrayList<Manager>();

        while(rs.next()) {
            var record = new Manager(rs);
            records.add(record);
        }

        return records;
    }

    public List<Manager> getAllAsc() throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM managers ORDER BY salary ASC";

        ResultSet rs = jdbcService.getStatement().executeQuery(sql);
        var records = new ArrayList<Manager>();

        while(rs.next()) {
            var record = new Manager(rs);
            records.add(record);
        }

        return records;
    }

    public List<Manager> getAllDesc() throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM managers ORDER BY salary DESC";

        ResultSet rs = jdbcService.getStatement().executeQuery(sql);
        var records = new ArrayList<Manager>();

        while(rs.next()) {
            var record = new Manager(rs);
            records.add(record);
        }

        return records;
    }

    @Override
    public void add(Manager manager) throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String query = "INSERT INTO managers (salary, firstName, lastName, bonus) VALUES (?, ?, ?, ?)";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setFloat(1, manager.getSalary());
        prep.setString(2, manager.getFirstName());
        prep.setString(3, manager.getLastName());
        prep.setFloat(4, manager.getBonus());

        prep.execute();
        prep.close();
    }

    @Override
    public void update(Manager manager) throws SQLException {
        get(manager.getId());
        var jdbcService = JDBCService.getInstance();
        String query = "UPDATE managers SET salary = ?, firstName = ?, lastName = ?, bonus = ? WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setFloat(1, manager.getSalary());
        prep.setString(2, manager.getFirstName());
        prep.setString(3, manager.getLastName());
        prep.setFloat(4, manager.getBonus());
        prep.setInt(5, manager.getId());

        prep.executeUpdate();
        prep.close();
    }

    @Override
    public void delete(int id) throws SQLException {
        get(id);
        var jdbcService = JDBCService.getInstance();
        String query = "DELETE FROM managers WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setInt(1, id);

        prep.execute();
        prep.close();
    }
}

