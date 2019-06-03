
/**
 * Das Interface stellt einen generischen Binnaeren Suchbaum dar.
 * @author Quang Huy Nguyen, Michael Babic
 *
 * @param <T>
 */
public interface Baum<T> {
	/**
	 * Fuegt ein Element in den Baum hinzu.
	 * @param element das eingefuegte Element
	 * @return void
	 */
	void insert (T element);
	
	/**
	 * Geben alle Knoten des Baum in Hauptreihenfolge aus.
	 * @param 
	 * @return
	 */
	void preOrder ();
	
	/**
	 * Geben alle Knoten des Baum in symmetrisch aus.
	 * @param 
	 * @return
	 */
	void inOrder ();
	
	/**
	 * Geben alle Knoten des Baum in Nebenreihenfolge aus.
	 * @param 
	 * @return
	 */
	void postOrder ();
	
	/**
	 * Liefert die Summe der Knoten, die Intergerwert zwischen min und max haben, zur�ck.
	 * @param min der kleinste Wert eine Knote erreichen kann
	 * @param max der gro�este Wert eine Knote erreichen kann
	 * @return die gesuchte Summe
	 */
	int summeBerechnen (int min, int max);
	
	public int getCount ();
	public void resetCount ();
}
