#cpuid.d sample program to extract the processor vendor id

.section .data	# ���ݶ�����
	msg : .ascii "the processor vendor id is 'xxxxxxxxxxxx'\n"	# Ҫ������ַ���
	len = . - msg	# �ִ�����

.section .text	# ���������
.global _start	# ָ����ں���

_start:		# ����Ļ����ʾһ���ַ���
	nop	# ���GDB��"b *_start"�޷������ϵ��bug����ʱʹ��"b *_start+1"����
	
	movl $0, %eax
	cpuid
	movl $msg, %edi
	movl %ebx, 28(%edi)
	movl %edx, 32(%edi)
	movl %ecx, 36(%edi)
	
	movl $len, %edx	# ���������ַ�������
	movl $msg, %ecx	# ��������Ҫ��ʾ���ַ���
	movl $1, %ebx	# ����һ���ļ�������(stdout) 
	movl $4, %eax	# ϵͳ���ú�(sys_write) 
	int  $0x80	# �����ں˹���
	
	# �˳�����
	movl $0,%ebx	# ����һ���˳�����
	movl $1,%eax	# ϵͳ���ú�(sys_exit) 
	int  $0x80	# �����ں˹���
