package services;

import models.accounts.DebitAccount;
import utilities.jdbc.JDBCService;
import utilities.jdbc.JDBCServiceInterface;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

public class DebitAccountService implements JDBCServiceInterface<DebitAccount> {
    private static DebitAccountService instance = null;

    public static DebitAccountService getInstance() {
        if (instance == null)
        {
            instance = new DebitAccountService();
        }
        return instance;
    }

    @Override
    public DebitAccount get(int id) throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM debitAccounts WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(sql);
        prep.setInt(1, id);

        prep.execute();
        prep.getResultSet().next();

        return new DebitAccount(prep.getResultSet());
    }

    @Override
    public List<DebitAccount> getAll() throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM debitAccounts";

        ResultSet rs = jdbcService.getStatement().executeQuery(sql);
        var records = new ArrayList<DebitAccount>();

        while(rs.next()) {
            var record = new DebitAccount(rs);
            records.add(record);
        }

        return records;
    }

    @Override
    public void add(DebitAccount debitAccount) throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String query = "INSERT INTO debitAccounts (bank, amount, currency, customerId, interestRate) VALUES (?, ?, ?, ?, ?)";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setString(1, debitAccount.getBank());
        prep.setFloat(2, debitAccount.getAmount());
        prep.setString(3, debitAccount.getCurrency());
        prep.setInt(4, debitAccount.getCustomerId());
        prep.setFloat(5, debitAccount.getInterestRate());

        prep.execute();
        prep.close();
    }

    @Override
    public void update(DebitAccount debitAccount) throws SQLException {
        get(debitAccount.getId());
        var jdbcService = JDBCService.getInstance();
        String query = "UPDATE debitAccounts SET bank = ?, amount = ?, currency = ?, customerId = ?, interestRate = ? WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setString(1, debitAccount.getBank());
        prep.setFloat(2, debitAccount.getAmount());
        prep.setString(3, debitAccount.getCurrency());
        prep.setInt(4, debitAccount.getCustomerId());
        prep.setFloat(5, debitAccount.getInterestRate());
        prep.setInt(6, debitAccount.getId());

        prep.executeUpdate();
        prep.close();
    }

    @Override
    public void delete(int id) throws SQLException {
        get(id);
        var jdbcService = JDBCService.getInstance();
        String query = "DELETE FROM debitAccounts WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setInt(1, id);

        prep.execute();
        prep.close();
    }
}

