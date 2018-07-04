package mylistenner;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JFileChooser;
import userinterface.Layout;

public class ProcessFileListenner implements ActionListener {

	private Layout layout;
	
	private void setLayout() {
		layout = new Layout();
	}
	JFileChooser jFileChooser = new JFileChooser();  //创建文件选择类准备创建文件对话框
	
	@Override
	public void actionPerformed(ActionEvent e) {
		int status = -1;
		setLayout();
		if (e.getActionCommand() == "Open File") {  //点击了 打开文件 对话框
			status = jFileChooser.showOpenDialog(null);  //创建对话框，在页面居中显示
			if (status == JFileChooser.APPROVE_OPTION) {
				System.out.println("You choose the approve option.");
				//打开文件，显示于新标签页，注意异常处理。
			}
		}
		else if (e.getActionCommand() == "Save File") {
			status = jFileChooser.showSaveDialog(null);  //创建对话框，在页面居中显示
			if (status == JFileChooser.APPROVE_OPTION) {
				//保存文件，注意异常处理。注意是否已经保存过这一文件。
				System.out.println("You choose the approve option.");
			}
		}
		else if (e.getActionCommand() == "New File") {
			layout.createTab("newfile" + layout.getTabNumber(), "");			
		}
	}

}
