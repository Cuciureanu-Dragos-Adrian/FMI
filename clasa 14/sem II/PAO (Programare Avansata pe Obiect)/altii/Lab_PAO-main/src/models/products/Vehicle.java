package models.products;

public abstract class Vehicle extends Product{
    protected final int wheelNumber;
    protected final int doorNumber;
    protected final int seatNumber;

    protected Vehicle(String name, double price, int wheelNumber, int doorNumber, int seatNumber) {
        super(name, price);
        this.wheelNumber = wheelNumber;
        this.seatNumber = seatNumber;
        this.doorNumber = doorNumber;
    }

    protected Vehicle(String id, String name, double price, int wheelNumber, int doorNumber, int seatNumber) {
        super(id, name, price);
        this.wheelNumber = wheelNumber;
        this.seatNumber = seatNumber;
        this.doorNumber = doorNumber;
    }

    @Override
    public String toString() {
        return super.toString() + "\n\t This vehicle has " + this.doorNumber + " doors and " + this.seatNumber + " seats.";
    }
}
