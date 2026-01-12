import java.sql.SQLOutput;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Examen2018Mai {
    public static void main(String[] args) {
        task2();
    }

    public static void task2(){
        List<Produs> products = Arrays.asList(
                new Produs("MegaJava", "r1", 2400, 10000),
                new Produs("renault", "r2", 3000, 300),
                new Produs("MegaJava", "r3", 200, 4500),
                new Produs("MegaJava", "r1", 2600, 2000),
                new Produs("audi", "a1", 4, 15000),
                new Produs("dacia", "d1", 4, 5000)
        );

//        Examen2018MaiTask2.a(products);
//        Examen2018MaiTask2.b(products);
//        System.out.println(Examen2018MaiTask2.c(products));
//        Examen2018MaiTask2.d(products);
        Examen2018MaiTask2.e(products);
    }
}


class Produs{
    String firma;
    String produs;
    int cantitate;
    float pret_unitar;

    public Produs(String firma, String produs, int cantitate, float pret_unitar) {
        this.firma = firma;
        this.produs = produs;
        this.cantitate = cantitate;
        this.pret_unitar = pret_unitar;
    }

    public String getFirma() {
        return firma;
    }

    public String getProdus() {
        return produs;
    }

    public int getCantitate() {
        return cantitate;
    }

    public float getPret_unitar() {
        return pret_unitar;
    }

    public void setFirma(String firma) {
        this.firma = firma;
    }

    public void setProdus(String produs) {
        this.produs = produs;
    }

    public void setCantitate(int cantitate) {
        this.cantitate = cantitate;
    }

    public void setPret_unitar(float pret_unitar) {
        this.pret_unitar = pret_unitar;
    }


    @Override
    public String toString() {
        return "Produs{" +
                "firma='" + firma + '\'' +
                ", produs='" + produs + '\'' +
                ", cantitate=" + cantitate +
                ", pret_unitar=" + pret_unitar +
                '}';
    }
}

class Examen2018MaiTask2{
    static void a(List<Produs> products){
        products.stream()
                .filter(x -> x.getFirma().equals("MegaJava"))
                .sorted(Comparator.comparing(Produs::getPret_unitar).reversed())
                .forEach(System.out::println);
    }

    static void b(List<Produs> products){
        products.stream()
                .map(Produs::getProdus)
                .distinct()
                .forEach(System.out::println);
    }

    static List<Produs> c(List<Produs> products){
        return products.stream()
                .filter(x -> x.getPret_unitar() >= 1000)
                .toList();
    }

    static void d(List<Produs> products){
        products.stream()
                .collect(Collectors.groupingBy(Produs::getFirma, Collectors.mapping(Produs::getProdus, Collectors.toSet())))
                .entrySet()
                .forEach(System.out::println);
    }

    static void e(List<Produs> products){
        products.stream()
                .map(Produs::getProdus)
                .sorted(Comparator.comparing(Function.identity()))
                .forEach(System.out::println);
    }
}
