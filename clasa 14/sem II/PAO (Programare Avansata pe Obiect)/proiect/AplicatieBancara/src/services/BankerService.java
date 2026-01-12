package services;

import models.employees.Banker;
import utilities.jdbc.JDBCService;
import utilities.jdbc.JDBCServiceInterface;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

public class BankerService implements JDBCServiceInterface<Banker> {
    private static BankerService instance = null;

    public static BankerService getInstance() {
        if (instance == null)
        {
            instance = new BankerService();
        }
        return instance;
    }

    @Override
    public Banker get(int id) throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM bankers WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(sql);
        prep.setInt(1, id);

        prep.execute();
        prep.getResultSet().next();

        return new Banker(prep.getResultSet());
    }

    @Override
    public List<Banker> getAll() throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM bankers";

        ResultSet rs = jdbcService.getStatement().executeQuery(sql);
        var records = new ArrayList<Banker>();

        while(rs.next()) {
            var record = new Banker(rs);
            records.add(record);
        }

        return records;
    }

    public List<Banker> getAllAsc() throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM bankers ORDER BY salary ASC";

        ResultSet rs = jdbcService.getStatement().executeQuery(sql);
        var records = new ArrayList<Banker>();

        while(rs.next()) {
            var record = new Banker(rs);
            records.add(record);
        }

        return records;
    }

    public List<Banker> getAllDesc() throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM bankers ORDER BY salary DESC";

        ResultSet rs = jdbcService.getStatement().executeQuery(sql);
        var records = new ArrayList<Banker>();

        while(rs.next()) {
            var record = new Banker(rs);
            records.add(record);
        }

        return records;
    }

    @Override
    public void add(Banker banker) throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String query = "INSERT INTO bankers (salary, firstName, lastName, workedFreeDays) VALUES (?, ?, ?, ?)";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setFloat(1, banker.getSalary());
        prep.setString(2, banker.getFirstName());
        prep.setString(3, banker.getLastName());
        prep.setFloat(4, banker.getWorkedFreeDays());

        prep.execute();
        prep.close();
    }

    @Override
    public void update(Banker banker) throws SQLException {
        get(banker.getId());
        var jdbcService = JDBCService.getInstance();
        String query = "UPDATE bankers SET salary = ?, firstName = ?, lastName = ?, workedFreeDays = ? WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setFloat(1, banker.getSalary());
        prep.setString(2, banker.getFirstName());
        prep.setString(3, banker.getLastName());
        prep.setFloat(4, banker.getWorkedFreeDays());
        prep.setInt(5, banker.getId());

        prep.executeUpdate();
        prep.close();
    }

    @Override
    public void delete(int id) throws SQLException {
        get(id);
        var jdbcService = JDBCService.getInstance();
        String query = "DELETE FROM bankers WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setInt(1, id);

        prep.execute();
        prep.close();
    }
}
