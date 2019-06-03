

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class BinarySearchTreeTest {
	private Baum<Integer> array; 
	private Baum<Integer> verlinkung; 
	@Test
	void testArray() {
		
		//Knoten in Baum einzuf�gt werden
		array = new arrayEinbettung<Integer>();
		array.insert(5);
		array.insert(7);
		array.insert(6);
		array.insert(3);
		array.insert(2);
		array.insert(4);
		array.insert(9);
		array.insert(19);
		array.insert(15);
		
		System.out.println("Binaer Suchbaum:");
		System.out.println("\nArray Einbettung: ");
		
		//Test 3 verschiedene Ausgabe
		
		System.out.println("\nPostorder: ");
		array.postOrder();
		System.out.println("\nPreorder: ");
		array.preOrder();
		System.out.println("\nInorder: ");
		array.inOrder();
		
		//Average Case
		int sum1a = array.summeBerechnen(1, 1);
		assertEquals(0, sum1a);
		int sum1b = array.summeBerechnen(20, 20);
		assertEquals(0, sum1b);
				
		//Best Case
		int sum2 = array.summeBerechnen(4,6);
		assertEquals(15, sum2);
								
		//Worst Case
		int sum3 = array.summeBerechnen(20, 1);
		assertEquals(70, sum3);
	}
	
	@Test
	void testVerlinkung() {
		
		//Knoten in Baum einzuf�gt werden
		verlinkung = new verlinkungBaum<Integer>();
		verlinkung.insert(5);
		verlinkung.insert(7);
		verlinkung.insert(6);
		verlinkung.insert(3);
		verlinkung.insert(2);
		verlinkung.insert(4);
		verlinkung.insert(9);
		verlinkung.insert(19);
		verlinkung.insert(15);
		
		System.out.println("\n");
		System.out.println("\nVerlinkung der Knoten: ");
		
		//Test 3 verschiedene Ausgabe
		
		System.out.println("\nPostorder: ");
		verlinkung.postOrder();
		System.out.println("\nPreorder: ");
		verlinkung.preOrder();
		System.out.println("\nInorder: ");
		verlinkung.inOrder();
		
//		//Average Case
//		int sum1a = verlinkung.summeBerechnen(1, 1);
//		assertEquals(0, sum1a);
//		int sum1b = verlinkung.summeBerechnen(20, 20);
//		assertEquals(0, sum1b);
						
		//Best Case
		int sum2 = verlinkung.summeBerechnen(4,6);
		System.out.println("\nCount in Best Case: " + verlinkung.getCount());
		assertEquals(15, sum2);
						
		//Worst Case
		verlinkung.resetCount();
		int sum3 = verlinkung.summeBerechnen(0, 6);
		System.out.println("Count in Worst Case: " + verlinkung.getCount());
		assertEquals(20, sum3);
	}
}
