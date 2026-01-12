package services;

import java.util.Scanner;

import static java.lang.Character.isDigit;

public class Utilities {

    /** Reads input from a scanner until an integer is given. Checks if the integer is in a given interval.
     *
     */
    public static int readIntInInterval(Scanner scanner, int lowerBound, int upperBound){
        int input = 0;
        boolean notInteger = true;

        while (notInteger) {
            try {
                input = scanner.nextInt();
                if (input < lowerBound || input > upperBound) { // option number was incorrect
                    System.out.println("Incorrect integer! Try again.");
                    continue;
                }
                notInteger = false;
            } catch (Exception e) {
                scanner.next(); //clear wrong input
                System.out.println("Please input an integer!");
            }
        }
        return input;
    }

    /** Reads input from a scanner until a double is given. Checks if the value is in a given interval.
     *
     */
    public static double readDoubleInInterval(Scanner scanner, int lowerBound, int upperBound){
        double input = 0;
        boolean notDouble = true;

        while (notDouble) {
            try {
                input = scanner.nextDouble();
                if(input < lowerBound) {
                    System.out.println("Input must be larger than " + lowerBound);
                    continue;
                }

                if(input > upperBound) {
                    System.out.println("Input must be smaller than " + upperBound);
                    continue;
                }

                notDouble = false;
            } catch (Exception e) {
                scanner.next(); //clear wrong input
                System.out.println("Please input a number!");
            }
        }
        return input;
    }

    public static boolean containsOnlyDigits(String input){
        for(int index = 0; index < input.length(); index++)
            if(!isDigit(input.charAt(index)))
                return false;

        return true;
    }

}
