package mylistenner;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import userinterface.Layout;

public class TabButtonListenner implements ActionListener {

	Layout layout;
	
	private void setLayout() {
		layout = new Layout();
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		setLayout();
		JButton button = (JButton)e.getSource();
		layout.deleteTabNamed(button.getToolTipText().substring(6));   //tooltip从第6位到最后即为标签页名字
	}
}
