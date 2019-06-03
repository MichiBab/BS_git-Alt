

/**
 * Ein Binaer Suchbaum wurde als ArrayEinbettung implementiert.
 * @author Quang Huy Nguyen
 *
 * @param <T>
 */
/**
 * @author acj039
 *
 * @param <T>
 */
public class arrayEinbettung<T extends Comparable<T>> implements Baum<T> {
	
	private Knoten<T> [] array;
	/**
	 * Das array wird mit 10 Objekten automatisch initialisiert.
	 */
	
	@SuppressWarnings("unchecked")
	public arrayEinbettung ()
	{
		array = new Knoten [10];
	}
	
	/**
	 * Fuegt ein Element in den Baum hinzu.
	 * @param element das eingefuegte Element
	 * @return void
	 */
	public void insert (T elem)
	{
		Knoten<T> node = new Knoten<T> (elem);
		// Addiert das erste Elem in Wurzel des Baum
		if (array[1] == null)
		{
			array[1] = node;
		}
		else
		{
			insertRec (1, elem);
		}
	}
	
	/**
	 * Fuegt ein Element in gewueschte Position Baum ein.
	 * @param index gewuenschte Position in Suchbaum
	 * @param elem einzufuegte Element
	 */
	
	private void insertRec (int index, T elem)
	{
		Knoten<T> node = new Knoten<T> (elem);
		// Compare 2 Knoten zuerst
		if (array[index].getElem().compareTo(elem) < 0)
		{
			addiereRechts (index);
			if (array[index*2 + 1] == null)
			{
				array[index*2 + 1] = node;
			}
			else 
			{
				insertRec (index*2+1, elem);
			}
		}
		else if (array[index].getElem().compareTo(elem) > 0)
		{
			addiereLinks (index);
			if (array[index*2] == null)
			{
				array[index*2] = node;
			}
			else 
			{
				insertRec (index*2, elem);
			}
		}
		else
		{
			System.out.println("Knote wurde schon in Baum einzufuegt!");
		}
		array[index].addierenInf((int) elem);
	}
	
	/**
	 * Erstellen ein double-length Array wenn das Index vom SohnLinks �berschreitet.
	 * @param index die Postion des Vater-Knotes.
	 */
	@SuppressWarnings("unchecked")
	private void addiereLinks (int index)
	{
		if (index*2 >= array.length)
		{
			Knoten<T> [] temp = new Knoten [array.length*2];
			System.arraycopy(array, 0, temp, 0, array.length);
			array = temp;
		}
	}
	
	/**
	 * Erstellen ein double-length Array wenn das Index vom SohnRechts �berschreitet.
	 * @param index die Postion des Vater-Knotes.
	 */
	@SuppressWarnings("unchecked")
	private void addiereRechts (int index)
	{
		if ((index*2)+1>= array.length)
		{
			Knoten<T> [] temp = new Knoten [array.length*2];
			System.arraycopy(array, 0, temp, 0, array.length);
			array = temp;
		}
	}
	
	/**
	 * Geben alle Knoten des Baum in symmetrisch aus.
	 * @param 
	 * @return
	 */
	public void inOrder ()
	{
		inOrderRec(1);
	}
	
	/**
	 * Geben das Element an gewissene Index aus. 
	 * @param index Position des Element
	 */
	private void inOrderRec (int index)
	{
		addiereRechts(index);
		if ((index*2) <= array.length && array[index*2] != null)
		{
			inOrderRec (index*2);
		}
		
		System.out.print(array[index].getKey() + " ");
		
		if ((index*2 + 1) <= array.length && array[index*2 + 1] != null)
		{
			inOrderRec (index*2+1);
		}
	}
	
	/**
	 * Geben alle Knoten des Baum in Hauptreihenfolge aus.
	 * @param 
	 * @return
	 */
	public void preOrder ()
	{
		preOrderRec(1);
	}
	
	/**
	 * Geben das Element an gewissene Index aus. 
	 * @param index Position des Element
	 */
	
	private void preOrderRec (int index)
	{
		System.out.print(array[index].getKey() + " ");
		addiereRechts(index);
		if ((index*2) <= array.length && array[index*2] != null)
		{
			preOrderRec (index*2);
		}
		
		if ((index*2 + 1) <= array.length && array[index*2 + 1] != null)
		{
			preOrderRec (index*2+1);
		}
	}
	
	/**
	 * Geben alle Knoten des Baum in Nebenreihenfolge aus.
	 * @param 
	 * @return
	 */
	public void postOrder ()
	{
		postOrderRec(1);
	}
	
	/**
	 * Geben das Element an gewissene Index aus. 
	 * @param index Position des Element
	 */
	private void postOrderRec (int index)
	{	
		addiereRechts(index);
		if ((index*2) <= array.length && array[index*2] != null)
		{
			postOrderRec (index*2);
		}
		
		if ((index*2 + 1) <= array.length && array[index*2 + 1] != null)
		{
			postOrderRec (index*2+1);
		}
		
		System.out.print(array[index].getKey() + " ");
	}
	
	/**
	 * Liefert die Summe der Knoten, die Intergerwert zwischen min und max haben, zur�ck.
	 * @param min der kleinste Wert eine Knote erreichen kann
	 * @param max der gro�este Wert eine Knote erreichen kann
	 * @return die gesuchte Summe
	 */
	public int summeBerechnen (int min, int max)
	{
		if(max < min) {
			int tmp;
			tmp = max;
			max = min;
			min = tmp;
		}
		int sumWurzel, sumMin, sumMax, ergebnis;
		sumWurzel = array[1].additionInf;
		sumMin = summeKleinerAlsMin(1, min);
		sumMax = summeGroesserAlsMax (1, max);
		ergebnis = sumWurzel - sumMin - sumMax;
		return ergebnis;
	}
	
	private int summeKleinerAlsMin (int index, int min)
	{
		if (array[index] == null)
		{
			return 0; // Abbruch Bedingung
		}
		else
		{
			if (array[index].getKey() > min)
			{
				return summeKleinerAlsMin (index*2, min);
			}
			else if (array[index].getKey() == min)
			{
				if (array[index*2] == null)
				{
					return 0;
				}
				else
				{
					return array[index*2].additionInf;
				}
			}
			else 
			{
				int sum = array[index].getKey();
				if (array[index*2] != null)
				{
					sum += array[index*2].additionInf;
				}
				return sum + summeKleinerAlsMin(index*2+1, min);
			}
		}
	}
	
	private int summeGroesserAlsMax (int index, int max)
	{
		if (array[index] == null)
		{
			return 0; // Abbruch Bedingung
		}
		else
		{
			if (array[index].getKey() < max)
			{
				return summeGroesserAlsMax (index*2+1, max);
			}
			else if (array[index].getKey() == max)
			{
				if (array[index*2+1] == null)
				{
					return 0;
				}
				else
				{
					return array[index*2+1].additionInf;
				}
			}
			else 
			{
				int sum = array[index].getKey();
				if (array[index*2+1] != null)
				{
					sum += array[index*2+1].additionInf;
				}
				return sum + summeGroesserAlsMax(index*2, max);
			}
		}
	}
	
	public int getCount ()
	{
		return 0;
	}
	public void resetCount ()
	{
		
	}
}
