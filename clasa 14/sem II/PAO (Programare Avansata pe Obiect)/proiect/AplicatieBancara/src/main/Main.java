package main;

import java.sql.SQLException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws SQLException, Exception {
        Scanner sc = new Scanner(System.in);
        MainMenu.menu(sc);
    }
}

