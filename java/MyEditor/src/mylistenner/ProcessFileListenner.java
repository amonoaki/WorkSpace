package mylistenner;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.JFileChooser;
import javax.swing.JPanel;
import javax.swing.JTextArea;

import userinterface.Layout;

public class ProcessFileListenner implements ActionListener {

	private Layout layout;

	public ProcessFileListenner(Layout layout) {
		super();
		this.layout = layout;
	}

	private File file;
 	JFileChooser fileChooser = new JFileChooser();  //创建文件选择类准备创建文件对话框

	@Override
	public void actionPerformed(ActionEvent event) {
		int status = -1;
		
		if (event.getActionCommand() == "Open File") {  //点击了 打开文件 对话框
			
			status = fileChooser.showOpenDialog(null);  //创建对话框，在页面居中显示

			if (status == JFileChooser.APPROVE_OPTION) {
				file = fileChooser.getSelectedFile();
				String fileName = file.getName();
				try {
					layout.createTab(fileName, "");
					JTextArea page = (JTextArea)layout.getTextArea(fileName);
					//创建输入流, 读取文件并显示
					BufferedReader in = new BufferedReader(new FileReader(file));
					String str = null;
					while((str = in.readLine()) != null) {
						//byte[] str1 = str.getBytes("utf-8");
						page.append(str);
						page.append("\n");  //手动换行
					}
					in.close();
					page.setCaretPosition(page.getDocument().getLength());  //将光标放在文本末尾
					layout.setActiveTabNamed(fileName);  //将新建的选项卡设置为活动的选项卡
				}
				catch(Exception e) {
					e.toString();
				}
				
				JPanel tabPanel = (JPanel)layout.getTabComponent();
				tabPanel.setToolTipText(file.getAbsolutePath());
			}
		}
		else if (event.getActionCommand() == "Save File") {
			
			JPanel tabPanel = (JPanel)layout.getTabComponent();
			String fileName = tabPanel.getToolTipText();
			file = new File(fileName);
			
			if (!file.exists()) {  //如果文件存在则直接保存即可
				status = fileChooser.showSaveDialog(null);  //创建对话框，在页面居中显示
				if (status == JFileChooser.APPROVE_OPTION) {
					file = fileChooser.getSelectedFile();
					tabPanel.setToolTipText(file.getAbsolutePath());
					try {
						//创建文档
						file.createNewFile();
					}
					catch(Exception e) {
						e.toString();
					}
				}
			}
			
			try {
				//创建输出流
				BufferedWriter out = new BufferedWriter(new FileWriter(file));
				//获取正在编辑的page
				JTextArea page = (JTextArea)layout.getTextArea();
				//将文本写入输出流
				String text = page.getText();
				out.write(text);
				out.flush();
				out.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		else if (event.getActionCommand() == "New File") {
			layout.createTab("newfile" + layout.getTabNumber(), "");
		}
	}

}
