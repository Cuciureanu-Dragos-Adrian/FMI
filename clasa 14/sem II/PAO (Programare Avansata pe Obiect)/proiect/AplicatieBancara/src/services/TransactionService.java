package services;

import models.transactions.Transaction;
import utilities.jdbc.JDBCService;
import utilities.jdbc.JDBCServiceInterface;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

public class TransactionService implements JDBCServiceInterface<Transaction> {
    private static TransactionService instance = null;

    public static TransactionService getInstance() {
        if (instance == null)
        {
            instance = new TransactionService();
        }
        return instance;
    }

    @Override
    public Transaction get(int id) throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM transactions WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(sql);
        prep.setInt(1, id);

        prep.execute();
        prep.getResultSet().next();

        return new Transaction(prep.getResultSet());
    }

    @Override
    public List<Transaction> getAll() throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM transactions";

        ResultSet rs = jdbcService.getStatement().executeQuery(sql);
        var records = new ArrayList<Transaction>();

        while(rs.next()) {
            var record = new Transaction(rs);
            records.add(record);
        }

        return records;
    }

    @Override
    public void add(Transaction transaction) throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String query = "INSERT INTO transactions (senderId, receiverId, amount, commission) VALUES (?, ?, ?, ?)";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setFloat(1, transaction.getSenderId());
        prep.setFloat(2, transaction.getReceiverId());
        prep.setFloat(3, transaction.getAmount());
        prep.setFloat(4, transaction.getCommission());

        prep.execute();
        prep.close();
    }

    @Override
    public void update(Transaction transaction) throws SQLException {
        get(transaction.getId());
        var jdbcService = JDBCService.getInstance();
        String query = "UPDATE transactions SET senderId = ?, receiverId = ?, amount = ?, commission = ? WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setFloat(1, transaction.getSenderId());
        prep.setFloat(2, transaction.getReceiverId());
        prep.setFloat(3, transaction.getAmount());
        prep.setFloat(4, transaction.getCommission());
        prep.setInt(5, transaction.getId());

        prep.executeUpdate();
        prep.close();
    }

    @Override
    public void delete(int id) throws SQLException {
        get(id);
        var jdbcService = JDBCService.getInstance();
        String query = "DELETE FROM transactions WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setInt(1, id);

        prep.execute();
        prep.close();
    }
}
