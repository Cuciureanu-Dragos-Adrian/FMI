import java.sql.*;
import java.util.*;


public class main {
    public static void main(String[] args) throws InterruptedException {
        task3();

    }

    public static void task2(){
        List<Automobil> automobilList = Arrays.asList(
                new Automobil("renault", "r1", 2400, 10000),
                new Automobil("renault", "r2", 3000, 3000),
                new Automobil("renault", "r3", 200, 4500),
                new Automobil("renault", "r1", 2600, 2000),
                new Automobil("audi", "a1", 4, 15000),
                new Automobil("dacia", "d1", 4, 5000)
        );

//        System.out.println(Task2.automobilsOver500Desc(automobilList));
//        System.out.println(Task2.distinctMarci(automobilList));
//        System.out.println(Task2.capac20003000(automobilList));
//        System.out.println(Task2.marcaModele(automobilList));
//        System.out.println(Task2.modelsForEachBrand(automobilList));

        System.out.println(Task2.marcaModeleBun(automobilList));
        System.out.println(Task2.marcaModeleBun2(automobilList));
        Task2.marcaModeleBun3(automobilList);
    }

    public static void task3() throws InterruptedException {
        String filePath = "src/exemplu_1.txt";

        Task3 thread = new Task3("yo", filePath);
        thread.start();
        thread.join();
    }

    public static void task4() throws SQLException {
        String jdbcDerbyURL = "jdbc:derby://localhost:1527/Angajati";
        Connection conn = DriverManager.getConnection(jdbcDerbyURL);

        float threshold = Float.parseFloat(new Scanner(System.in).nextLine());

        String query =
                """
                SELECT *
                FROM DateAngajati
                WHERE salariu >= ?
                """;

        PreparedStatement smt = conn.prepareStatement(query);
        smt.setFloat(1, threshold);

        ResultSet rs = smt.executeQuery();
        if (!rs.next())
            System.out.printf("Niciun angajat cu salariul >= %f", threshold);
        else {
            do {
                String cnp = rs.getString("cnp");
                String nume = rs.getString("nume");
                int varsta = rs.getInt("varsta");
                float salariu = rs.getFloat("salariu");
                System.out.printf("Angajat (%s, %s, %d, %.2f)%n", cnp, nume, varsta, salariu);
            } while (rs.next());
        }
    }

}

