

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
//		Baum<Integer> array = new arrayEinbettung<Integer>();
		Baum<Integer> verlinkung = new verlinkungBaum<Integer>();
		
//		System.out.println("Binärer Suchbaum:");
//		
//		System.out.println("\nArray Einbettung: ");
//		array.insert(5);
//		array.insert(7);
//		array.insert(6);
//		array.insert(3);
//		array.insert(2);
//		array.insert(4);
//		array.insert(9);
//		array.insert(19);
//		array.insert(15);
//		array.insert(7);
//		array.insert(16);
//		array.insert(30);
//		
//		System.out.println("\nPostorder: ");
//		array.postOrder();
//		System.out.println("\nPreorder: ");
//		array.preOrder();
//		System.out.println("\nInorder: ");
//		array.inOrder();
//		System.out.println("\nSumme zwischen Min und Max: " + array.summeBerechnen(5,6));
		
		System.out.println("\nVerlinkung Baum ");
		verlinkung.insert(17);
		verlinkung.insert(7);
		verlinkung.insert(6);
		verlinkung.insert(3);
		verlinkung.insert(2);
		verlinkung.insert(4);
		verlinkung.insert(9);
		verlinkung.insert(19);
		verlinkung.insert(15);
//		verlinkung.insert(7);
//		verlinkung.insert(16);
//		verlinkung.insert(30);
//		
//		System.out.println("\nPostorder: ");
//		verlinkung.postOrder();
//		System.out.println("\nPreorder: ");
//		verlinkung.preOrder();
//		System.out.println("\nInorder: ");
//		verlinkung.inOrder();
		System.out.println("\nSumme zwischen Min und Max: " + verlinkung.summeBerechnen(15,19));
		System.out.println("Count: " + verlinkung.getCount());
	}
	
}
