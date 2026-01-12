package database;

public class EmbeddedDatabaseConstants {

    public static final String ConnString = "jdbc:derby:paoDb;user=pao;password=pao";
    public static final String CreateString = "jdbc:derby:paoDb;create=true;user=pao;password=pao";
    public static final String CreatePfTable= """
            create table pf
            (id varchar(50) not null,
            lastName varchar(30),
            firstName varchar(30),
            pnc varchar(30),
            funds float(30),
            constraint primary_key_pj primary key (id))""";

    public static final String CreatePjTable= """
            create table pj
            (id varchar(50) not null,
            name varchar(30),
            fic varchar(30),
            funds float(30),
            constraint primary_key_pf primary key (id))""";

    public static final String CreateManagerTable= """
            create table manager
            (id varchar(50) not null,
            lastName varchar(30),
            firstName varchar(30),
            managerId varchar(50),
            salary float(30),
            constraint primary_key_manager primary key (id))""";

    public static final String CreateMechanicTable= """
            create table mechanic
            (id varchar(50) not null,
            lastName varchar(30),
            firstName varchar(30),
            managerId varchar(50),
            salary float(30),
            constraint primary_key_mechanic primary key (id))""";

    public static final String CreateSalesmanTable= """
            create table salesman
            (id varchar(50) not null,
            lastName varchar(30),
            firstName varchar(30),
            managerId varchar(50),
            salary float(30),
            saleNr int,
            constraint primary_key_salesman primary key (id))""";

    public static final String CreateMerchandiseTable= """
            create table merchandise
            (id varchar(50) not null,
            name varchar(30),
            price float(30),
            discount float(30),
            stock int,
            constraint primary_key_merchandise primary key (id))""";

    public static final String CreateCarTable= """
            create table car
            (id varchar(50) not null,
            name varchar(30),
            price float(30),
            discount float(30),
            wheelNumber int,
            doorNumber int,
            seatNumber int,
            carType varchar(30),
            constraint primary_key_car primary key (id))""";

    public static final String CreateUtilityVehicleTable= """
            create table utilityVehicle
            (id varchar(50) not null,
            name varchar(30),
            price float(30),
            discount float(30),
            wheelNumber int,
            doorNumber int,
            seatNumber int,
            utilityType varchar(30),
            maxLoad float(30),
            constraint primary_key_uv primary key (id))""";

}
