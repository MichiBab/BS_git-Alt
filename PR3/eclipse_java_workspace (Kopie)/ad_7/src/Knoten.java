
/**
 * Knote vom Suchbaum, die generische Daten haben.
 * @author Quang Huy NGuyen
 *
 * @param <T>
 */
public class Knoten <T extends Comparable<T>> {
	
	private T elem;
	private Knoten<T> links, rechts, vater;
	private int key;
	public int additionInf;
	/**
	 * Daten der Knote definiert.
	 * @param elem Daten der Knote
	 */
	public Knoten (T elem)
	{
		key = (int) elem;
		this.elem = elem;
		additionInf =(int) elem;
		links = rechts = vater = null;
	}
	
	/**
	 * Set SohnLinks einer Knote
	 * @param links
	 */
	public void setLinks (Knoten<T> links)
	{
		this.links = links;
	}
	
	/**
	 * Set SohnRechts einer Knote
	 * @param links
	 */
	public void setRechts (Knoten<T> rechts)
	{
		this.rechts = rechts;
	}
	
	/**
	 * Set Vater einer Knote
	 * @param links
	 */
	public void setVater (Knoten<T> vater)
	{
		this.vater = vater;
	}
	
	/**
	 * Get SohnLinks einer Knote
	 * @return Sohnlinks
	 */
	public Knoten <T> getLinks ()
	{
		return links;
	}
	
	/**
	 * Get SohnRechts einer Knote
	 * @return SohnRechts
	 */
	public Knoten <T> getRechts ()
	{
		return rechts;
	}
	
	/**
	 * Get Vater einer Knote
	 * @return Vater
	 */
	public Knoten <T> getVater ()
	{
		return vater;
	}
	
	/**
	 * Get Daten einer Knote
	 * @return Daten
	 */
	public T getElem ()
	{
		return elem;
	}
	
	public int getKey ()
	{
		return key;
	}
	
	public void addierenInf (int value)
	{
		additionInf += value;
	}
}
