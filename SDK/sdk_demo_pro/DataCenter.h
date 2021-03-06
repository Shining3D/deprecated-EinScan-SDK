#ifndef _DATA_CENTER_H_
#define _DATA_CENTER_H_
#include "msg_define.h"
#include <qmutex.h>

class demo_data_center
{
protected:
	demo_data_center();
	~demo_data_center();
public:
	static  demo_data_center* Instance();
	static  void  UnInstance();
	
	void free_point_memory(SN3D_CLOUD_POINT& point);
	bool allocate_point_memory(SN3D_CLOUD_POINT& point);
	bool allocate_mesh_trim(SN3D_TRI_MESH& mesh_trim);
	void free_mesh_trim(SN3D_TRI_MESH& mesh_trim);

	void get_scanner_rt(SN3D_SCANNER_RT& rt);
	void update_scanner_rt(SN3D_SCANNER_RT& rt);
	void update_current_cloud_point(SN3D_CLOUD_POINT& point);
	void update_whole_cloud_point(SN3D_CLOUD_POINT& point);
	void update_current_mark_point(SN3D_CLOUD_POINT& point);
	void update_whole_mark_point(SN3D_CLOUD_POINT& point);
	void update_mesh_trim(SN3D_TRI_MESH& mesh_trim);
	int delete_point(int start0, int end0, int start1, int end1, int start2, int end2, SN3D_CLOUD_POINT& remain);

	int save_whole_point(char* path);
	int save_whole_mark_point(char* path);
 
	int get_whole_marker_count();

	void clear_data();
	
	void  set_align_mode(int  align_mode);
	int   get_align_mode();
protected:
	static   demo_data_center* _instance;
	int       current_align_mode;
	QMutex				_mutx;
	SN3D_SCANNER_RT		_scanner_rt;
	SN3D_CLOUD_POINT	_current_point;
	SN3D_CLOUD_POINT	_whole_point;
	SN3D_CLOUD_POINT	_mark_point;
	SN3D_CLOUD_POINT	_whole_mark_point;
	SN3D_TRI_MESH		_mesh_trim;
};


#endif