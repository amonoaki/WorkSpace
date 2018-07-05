package mylistenner;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

import javax.swing.JFileChooser;
import javax.swing.JTextArea;

import userinterface.Layout;

public class ProcessFileListenner implements ActionListener {

	private Layout layout;
	private File file;
	JFileChooser fileChooser = new JFileChooser();  //创建文件选择类准备创建文件对话框

	private void setLayout() {
		layout = new Layout();
	}
	
	@Override
	public void actionPerformed(ActionEvent event) {
		int status = -1;
		setLayout();
		
		if (event.getActionCommand() == "Open File") {  //点击了 打开文件 对话框
			status = fileChooser.showOpenDialog(null);  //创建对话框，在页面居中显示
			if (status == JFileChooser.APPROVE_OPTION) {
				file = fileChooser.getSelectedFile();
				String fileName = file.getName();
				try {
					BufferedReader in = new BufferedReader(new FileReader(file));
					layout.createTab(fileName, "");
					JTextArea page = (JTextArea)layout.getTextAreaAtTabNamed(fileName);
					
					String str = null;
					while((str = in.readLine()) != null) {
						page.append(str);
						page.append("\n");  //手动换行
					}
					page.setCaretPosition(page.getDocument().getLength());  //将光标放在文本末尾
					in.close();
					layout.setActiveTabNamed(fileName);  //将新建的选项卡设置为活动的选项卡
				}
				catch(Exception e) {
					e.toString();
				}
			}
		}
		else if (event.getActionCommand() == "Save File") {
			status = fileChooser.showSaveDialog(null);  //创建对话框，在页面居中显示
			if (status == JFileChooser.APPROVE_OPTION) {
				//保存文件，注意异常处理。注意是否已经保存过这一文件。
				System.out.println("You choose the approve option.");
			}
		}
		else if (event.getActionCommand() == "New File") {
			layout.createTab("newfile" + layout.getTabNumber(), "");			
		}
	}

}
